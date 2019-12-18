#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  struct nl_msg nl_msg ;
struct nl_cb {int dummy; } ;

/* Variables and functions */
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  NL_AUTO_PID ; 
 int /*<<< orphan*/  NL_AUTO_SEQ ; 
 int /*<<< orphan*/  NL_CB_ACK ; 
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  NL_CB_FINISH ; 
 int /*<<< orphan*/  NL_CB_VALID ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  family ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  genl_family_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_put (struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle ; 
 struct nl_cb* nl_cb_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_cb_put (struct nl_cb*) ; 
 int /*<<< orphan*/  nl_cb_set (struct nl_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (struct nl_msg*,void*),int*) ; 
 int /*<<< orphan*/  nl_recvmsgs (int /*<<< orphan*/ ,struct nl_cb*) ; 
 int /*<<< orphan*/  nl_send_auto_complete (int /*<<< orphan*/ ,struct nl_msg*) ; 
 int /*<<< orphan*/  nl_wait_for_ack (int /*<<< orphan*/ ) ; 
 struct nl_msg* nlmsg_alloc () ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait_handler ; 

__attribute__((used)) static int
swlib_call(int cmd, int (*call)(struct nl_msg *, void *),
		int (*data)(struct nl_msg *, void *), void *arg)
{
	struct nl_msg *msg;
	struct nl_cb *cb = NULL;
	int finished;
	int flags = 0;
	int err = 0;

	msg = nlmsg_alloc();
	if (!msg) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}

	if (!data)
		flags |= NLM_F_DUMP;

	genlmsg_put(msg, NL_AUTO_PID, NL_AUTO_SEQ, genl_family_get_id(family), 0, flags, cmd, 0);
	if (data) {
		err = data(msg, arg);
		if (err < 0)
			goto nla_put_failure;
	}

	cb = nl_cb_alloc(NL_CB_CUSTOM);
	if (!cb) {
		fprintf(stderr, "nl_cb_alloc failed.\n");
		exit(1);
	}

	err = nl_send_auto_complete(handle, msg);
	if (err < 0) {
		fprintf(stderr, "nl_send_auto_complete failed: %d\n", err);
		goto out;
	}

	finished = 0;

	if (call)
		nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, call, arg);

	if (data)
		nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, wait_handler, &finished);
	else
		nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, wait_handler, &finished);

	err = nl_recvmsgs(handle, cb);
	if (err < 0) {
		goto out;
	}

	if (!finished)
		err = nl_wait_for_ack(handle);

out:
	if (cb)
		nl_cb_put(cb);
nla_put_failure:
	nlmsg_free(msg);
	return err;
}