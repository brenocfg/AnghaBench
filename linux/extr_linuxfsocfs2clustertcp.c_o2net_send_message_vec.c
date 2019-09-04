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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct o2net_status_wait {int ns_status; int /*<<< orphan*/  ns_sys_status; int /*<<< orphan*/  ns_wq; int /*<<< orphan*/  ns_id; int /*<<< orphan*/  ns_node_item; } ;
struct o2net_sock_container {int /*<<< orphan*/  sc_send_lock; int /*<<< orphan*/  sc_sock; } ;
struct o2net_send_tracking {int dummy; } ;
struct o2net_node {int /*<<< orphan*/  nn_sc_wq; } ;
struct o2net_msg {int iov_len; int /*<<< orphan*/  msg_num; struct o2net_msg* iov_base; } ;
struct kvec {int iov_len; int /*<<< orphan*/  msg_num; struct kvec* iov_base; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELOOP ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LIST_HEAD_INIT (int /*<<< orphan*/ ) ; 
 size_t O2NET_MAX_PAYLOAD_BYTES ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 size_t iov_length (struct iovec*,size_t) ; 
 int /*<<< orphan*/  kfree (struct o2net_msg*) ; 
 struct o2net_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct o2net_msg* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct o2net_msg*,struct o2net_msg*,size_t) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msglog (struct o2net_msg*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_complete_nsw (struct o2net_node*,struct o2net_status_wait*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_debug_add_nst (struct o2net_send_tracking*) ; 
 int /*<<< orphan*/  o2net_debug_del_nst (struct o2net_send_tracking*) ; 
 int /*<<< orphan*/  o2net_init_msg (struct o2net_msg*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_init_nst (struct o2net_send_tracking*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct o2net_node* o2net_nn_from_num (scalar_t__) ; 
 int /*<<< orphan*/  o2net_nsw_completed (struct o2net_node*,struct o2net_status_wait*) ; 
 int o2net_prep_nsw (struct o2net_node*,struct o2net_status_wait*) ; 
 int o2net_send_tcp_msg (int /*<<< orphan*/ ,struct o2net_msg*,size_t,int) ; 
 int /*<<< orphan*/  o2net_set_nst_msg_id (struct o2net_send_tracking*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_set_nst_send_time (struct o2net_send_tracking*) ; 
 int /*<<< orphan*/  o2net_set_nst_sock_container (struct o2net_send_tracking*,struct o2net_sock_container*) ; 
 int /*<<< orphan*/  o2net_set_nst_sock_time (struct o2net_send_tracking*) ; 
 int /*<<< orphan*/  o2net_set_nst_status_time (struct o2net_send_tracking*) ; 
 int o2net_sys_err_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_tx_can_proceed (struct o2net_node*,struct o2net_sock_container**,int*) ; 
 int /*<<< orphan*/  o2net_update_send_stats (struct o2net_send_tracking*,struct o2net_sock_container*) ; 
 int /*<<< orphan*/ * o2net_wq ; 
 scalar_t__ o2nm_this_node () ; 
 int /*<<< orphan*/  sc_put (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int o2net_send_message_vec(u32 msg_type, u32 key, struct kvec *caller_vec,
			   size_t caller_veclen, u8 target_node, int *status)
{
	int ret = 0;
	struct o2net_msg *msg = NULL;
	size_t veclen, caller_bytes = 0;
	struct kvec *vec = NULL;
	struct o2net_sock_container *sc = NULL;
	struct o2net_node *nn = o2net_nn_from_num(target_node);
	struct o2net_status_wait nsw = {
		.ns_node_item = LIST_HEAD_INIT(nsw.ns_node_item),
	};
	struct o2net_send_tracking nst;

	o2net_init_nst(&nst, msg_type, key, current, target_node);

	if (o2net_wq == NULL) {
		mlog(0, "attempt to tx without o2netd running\n");
		ret = -ESRCH;
		goto out;
	}

	if (caller_veclen == 0) {
		mlog(0, "bad kvec array length\n");
		ret = -EINVAL;
		goto out;
	}

	caller_bytes = iov_length((struct iovec *)caller_vec, caller_veclen);
	if (caller_bytes > O2NET_MAX_PAYLOAD_BYTES) {
		mlog(0, "total payload len %zu too large\n", caller_bytes);
		ret = -EINVAL;
		goto out;
	}

	if (target_node == o2nm_this_node()) {
		ret = -ELOOP;
		goto out;
	}

	o2net_debug_add_nst(&nst);

	o2net_set_nst_sock_time(&nst);

	wait_event(nn->nn_sc_wq, o2net_tx_can_proceed(nn, &sc, &ret));
	if (ret)
		goto out;

	o2net_set_nst_sock_container(&nst, sc);

	veclen = caller_veclen + 1;
	vec = kmalloc_array(veclen, sizeof(struct kvec), GFP_ATOMIC);
	if (vec == NULL) {
		mlog(0, "failed to %zu element kvec!\n", veclen);
		ret = -ENOMEM;
		goto out;
	}

	msg = kmalloc(sizeof(struct o2net_msg), GFP_ATOMIC);
	if (!msg) {
		mlog(0, "failed to allocate a o2net_msg!\n");
		ret = -ENOMEM;
		goto out;
	}

	o2net_init_msg(msg, caller_bytes, msg_type, key);

	vec[0].iov_len = sizeof(struct o2net_msg);
	vec[0].iov_base = msg;
	memcpy(&vec[1], caller_vec, caller_veclen * sizeof(struct kvec));

	ret = o2net_prep_nsw(nn, &nsw);
	if (ret)
		goto out;

	msg->msg_num = cpu_to_be32(nsw.ns_id);
	o2net_set_nst_msg_id(&nst, nsw.ns_id);

	o2net_set_nst_send_time(&nst);

	/* finally, convert the message header to network byte-order
	 * and send */
	mutex_lock(&sc->sc_send_lock);
	ret = o2net_send_tcp_msg(sc->sc_sock, vec, veclen,
				 sizeof(struct o2net_msg) + caller_bytes);
	mutex_unlock(&sc->sc_send_lock);
	msglog(msg, "sending returned %d\n", ret);
	if (ret < 0) {
		mlog(0, "error returned from o2net_send_tcp_msg=%d\n", ret);
		goto out;
	}

	/* wait on other node's handler */
	o2net_set_nst_status_time(&nst);
	wait_event(nsw.ns_wq, o2net_nsw_completed(nn, &nsw));

	o2net_update_send_stats(&nst, sc);

	/* Note that we avoid overwriting the callers status return
	 * variable if a system error was reported on the other
	 * side. Callers beware. */
	ret = o2net_sys_err_to_errno(nsw.ns_sys_status);
	if (status && !ret)
		*status = nsw.ns_status;

	mlog(0, "woken, returning system status %d, user status %d\n",
	     ret, nsw.ns_status);
out:
	o2net_debug_del_nst(&nst); /* must be before dropping sc and node */
	if (sc)
		sc_put(sc);
	kfree(vec);
	kfree(msg);
	o2net_complete_nsw(nn, &nsw, 0, 0, 0);
	return ret;
}