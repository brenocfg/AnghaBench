#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TCP_Server_Info {int in_flight; int max_in_flight; unsigned int reconnect_instance; scalar_t__ tcpStatus; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  hostname; int /*<<< orphan*/  CurrentMid; int /*<<< orphan*/  request_q; TYPE_1__* ops; } ;
struct TYPE_2__ {int* (* get_credits_field ) (struct TCP_Server_Info*,int) ;} ;

/* Variables and functions */
 int const CIFS_BLOCKING_OP ; 
 int CIFS_ECHO_OP ; 
 int const CIFS_NON_BLOCKING ; 
 int const CIFS_OP_MASK ; 
 int const CIFS_TIMEOUT_MASK ; 
 scalar_t__ CifsExiting ; 
 int EAGAIN ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 int ERESTARTSYS ; 
 int MAX_COMPOUND ; 
 long MAX_JIFFY_OFFSET ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_num_waiters_dec (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_num_waiters_inc (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  has_credits (struct TCP_Server_Info*,int*,int const) ; 
 long msecs_to_jiffies (int const) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int* stub1 (struct TCP_Server_Info*,int) ; 
 int /*<<< orphan*/  trace_smb3_credit_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int wait_event_killable_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int
wait_for_free_credits(struct TCP_Server_Info *server, const int num_credits,
		      const int timeout, const int flags,
		      unsigned int *instance)
{
	int rc;
	int *credits;
	int optype;
	long int t;

	if (timeout < 0)
		t = MAX_JIFFY_OFFSET;
	else
		t = msecs_to_jiffies(timeout);

	optype = flags & CIFS_OP_MASK;

	*instance = 0;

	credits = server->ops->get_credits_field(server, optype);
	/* Since an echo is already inflight, no need to wait to send another */
	if (*credits <= 0 && optype == CIFS_ECHO_OP)
		return -EAGAIN;

	spin_lock(&server->req_lock);
	if ((flags & CIFS_TIMEOUT_MASK) == CIFS_NON_BLOCKING) {
		/* oplock breaks must not be held up */
		server->in_flight++;
		if (server->in_flight > server->max_in_flight)
			server->max_in_flight = server->in_flight;
		*credits -= 1;
		*instance = server->reconnect_instance;
		spin_unlock(&server->req_lock);
		return 0;
	}

	while (1) {
		if (*credits < num_credits) {
			spin_unlock(&server->req_lock);
			cifs_num_waiters_inc(server);
			rc = wait_event_killable_timeout(server->request_q,
				has_credits(server, credits, num_credits), t);
			cifs_num_waiters_dec(server);
			if (!rc) {
				trace_smb3_credit_timeout(server->CurrentMid,
					server->hostname, num_credits);
				cifs_server_dbg(VFS, "wait timed out after %d ms\n",
					 timeout);
				return -ENOTSUPP;
			}
			if (rc == -ERESTARTSYS)
				return -ERESTARTSYS;
			spin_lock(&server->req_lock);
		} else {
			if (server->tcpStatus == CifsExiting) {
				spin_unlock(&server->req_lock);
				return -ENOENT;
			}

			/*
			 * For normal commands, reserve the last MAX_COMPOUND
			 * credits to compound requests.
			 * Otherwise these compounds could be permanently
			 * starved for credits by single-credit requests.
			 *
			 * To prevent spinning CPU, block this thread until
			 * there are >MAX_COMPOUND credits available.
			 * But only do this is we already have a lot of
			 * credits in flight to avoid triggering this check
			 * for servers that are slow to hand out credits on
			 * new sessions.
			 */
			if (!optype && num_credits == 1 &&
			    server->in_flight > 2 * MAX_COMPOUND &&
			    *credits <= MAX_COMPOUND) {
				spin_unlock(&server->req_lock);
				cifs_num_waiters_inc(server);
				rc = wait_event_killable_timeout(
					server->request_q,
					has_credits(server, credits,
						    MAX_COMPOUND + 1),
					t);
				cifs_num_waiters_dec(server);
				if (!rc) {
					trace_smb3_credit_timeout(
						server->CurrentMid,
						server->hostname, num_credits);
					cifs_server_dbg(VFS, "wait timed out after %d ms\n",
						 timeout);
					return -ENOTSUPP;
				}
				if (rc == -ERESTARTSYS)
					return -ERESTARTSYS;
				spin_lock(&server->req_lock);
				continue;
			}

			/*
			 * Can not count locking commands against total
			 * as they are allowed to block on server.
			 */

			/* update # of requests on the wire to server */
			if ((flags & CIFS_TIMEOUT_MASK) != CIFS_BLOCKING_OP) {
				*credits -= num_credits;
				server->in_flight += num_credits;
				if (server->in_flight > server->max_in_flight)
					server->max_in_flight = server->in_flight;
				*instance = server->reconnect_instance;
			}
			spin_unlock(&server->req_lock);
			break;
		}
	}
	return 0;
}