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
struct smb_rqst {int dummy; } ;
struct mid_q_entry {int /*<<< orphan*/  credits; int /*<<< orphan*/  qhead; int /*<<< orphan*/  mid_state; int /*<<< orphan*/ * handle; void* callback_data; int /*<<< orphan*/ * callback; int /*<<< orphan*/ * receive; } ;
struct cifs_credits {int value; unsigned int instance; } ;
struct TCP_Server_Info {unsigned int reconnect_instance; int sequence_number; int /*<<< orphan*/  srv_mutex; int /*<<< orphan*/  pending_mid_q; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  mid_receive_t ;
typedef  int /*<<< orphan*/  mid_handle_t ;
typedef  int /*<<< orphan*/  mid_callback_t ;
struct TYPE_2__ {struct mid_q_entry* (* setup_async_request ) (struct TCP_Server_Info*,struct smb_rqst*) ;} ;

/* Variables and functions */
 int const CIFS_HAS_CREDITS ; 
 int const CIFS_OP_MASK ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 scalar_t__ IS_ERR (struct mid_q_entry*) ; 
 int /*<<< orphan*/  MID_REQUEST_SUBMITTED ; 
 int PTR_ERR (struct mid_q_entry*) ; 
 int /*<<< orphan*/  add_credits_and_wake_if (struct TCP_Server_Info*,struct cifs_credits*,int) ; 
 int /*<<< orphan*/  cifs_delete_mid (struct mid_q_entry*) ; 
 int /*<<< orphan*/  cifs_in_send_dec (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_in_send_inc (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_save_when_sent (struct mid_q_entry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revert_current_mid (struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 
 int smb_send_rqst (struct TCP_Server_Info*,int,struct smb_rqst*,int const) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mid_q_entry* stub1 (struct TCP_Server_Info*,struct smb_rqst*) ; 
 int wait_for_free_request (struct TCP_Server_Info*,int const,unsigned int*) ; 

int
cifs_call_async(struct TCP_Server_Info *server, struct smb_rqst *rqst,
		mid_receive_t *receive, mid_callback_t *callback,
		mid_handle_t *handle, void *cbdata, const int flags,
		const struct cifs_credits *exist_credits)
{
	int rc;
	struct mid_q_entry *mid;
	struct cifs_credits credits = { .value = 0, .instance = 0 };
	unsigned int instance;
	int optype;

	optype = flags & CIFS_OP_MASK;

	if ((flags & CIFS_HAS_CREDITS) == 0) {
		rc = wait_for_free_request(server, flags, &instance);
		if (rc)
			return rc;
		credits.value = 1;
		credits.instance = instance;
	} else
		instance = exist_credits->instance;

	mutex_lock(&server->srv_mutex);

	/*
	 * We can't use credits obtained from the previous session to send this
	 * request. Check if there were reconnects after we obtained credits and
	 * return -EAGAIN in such cases to let callers handle it.
	 */
	if (instance != server->reconnect_instance) {
		mutex_unlock(&server->srv_mutex);
		add_credits_and_wake_if(server, &credits, optype);
		return -EAGAIN;
	}

	mid = server->ops->setup_async_request(server, rqst);
	if (IS_ERR(mid)) {
		mutex_unlock(&server->srv_mutex);
		add_credits_and_wake_if(server, &credits, optype);
		return PTR_ERR(mid);
	}

	mid->receive = receive;
	mid->callback = callback;
	mid->callback_data = cbdata;
	mid->handle = handle;
	mid->mid_state = MID_REQUEST_SUBMITTED;

	/* put it on the pending_mid_q */
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&mid->qhead, &server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);

	/*
	 * Need to store the time in mid before calling I/O. For call_async,
	 * I/O response may come back and free the mid entry on another thread.
	 */
	cifs_save_when_sent(mid);
	cifs_in_send_inc(server);
	rc = smb_send_rqst(server, 1, rqst, flags);
	cifs_in_send_dec(server);

	if (rc < 0) {
		revert_current_mid(server, mid->credits);
		server->sequence_number -= 2;
		cifs_delete_mid(mid);
	}

	mutex_unlock(&server->srv_mutex);

	if (rc == 0)
		return 0;

	add_credits_and_wake_if(server, &credits, optype);
	return rc;
}