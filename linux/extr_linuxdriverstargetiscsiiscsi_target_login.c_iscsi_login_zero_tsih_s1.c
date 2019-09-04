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
struct iscsi_session {int session_index; struct iscsi_session* sess_ops; int /*<<< orphan*/  se_sess; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  time2retain_timer; int /*<<< orphan*/  ttt_lock; int /*<<< orphan*/  session_usage_lock; int /*<<< orphan*/  cr_i_lock; int /*<<< orphan*/  cr_a_lock; int /*<<< orphan*/  conn_lock; int /*<<< orphan*/  cmdsn_mutex; int /*<<< orphan*/  session_waiting_on_uc_comp; int /*<<< orphan*/  session_wait_comp; int /*<<< orphan*/  reinstatement_comp; int /*<<< orphan*/  async_msg_comp; int /*<<< orphan*/  cr_inactive_list; int /*<<< orphan*/  cr_active_list; int /*<<< orphan*/  sess_ooo_cmdsn_list; int /*<<< orphan*/  sess_conn_list; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  isid; int /*<<< orphan*/  init_task_tag; } ;
struct iscsi_sess_ops {int dummy; } ;
struct iscsi_login_req {int /*<<< orphan*/  cmdsn; int /*<<< orphan*/  isid; int /*<<< orphan*/  itt; int /*<<< orphan*/  cid; } ;
struct iscsi_conn {int /*<<< orphan*/ * sess; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISCSI_LOGIN_STATUS_NO_RESOURCES ; 
 int /*<<< orphan*/  ISCSI_STATUS_CLS_TARGET_ERR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PROT_NORMAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ iscsi_login_set_conn_values (struct iscsi_session*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_handle_time2retain_timeout ; 
 int /*<<< orphan*/  iscsit_tx_login_rsp (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iscsi_session*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sess_ida ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_alloc_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_login_zero_tsih_s1(
	struct iscsi_conn *conn,
	unsigned char *buf)
{
	struct iscsi_session *sess = NULL;
	struct iscsi_login_req *pdu = (struct iscsi_login_req *)buf;
	int ret;

	sess = kzalloc(sizeof(struct iscsi_session), GFP_KERNEL);
	if (!sess) {
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		pr_err("Could not allocate memory for session\n");
		return -ENOMEM;
	}

	if (iscsi_login_set_conn_values(sess, conn, pdu->cid))
		goto free_sess;

	sess->init_task_tag	= pdu->itt;
	memcpy(&sess->isid, pdu->isid, 6);
	sess->exp_cmd_sn	= be32_to_cpu(pdu->cmdsn);
	INIT_LIST_HEAD(&sess->sess_conn_list);
	INIT_LIST_HEAD(&sess->sess_ooo_cmdsn_list);
	INIT_LIST_HEAD(&sess->cr_active_list);
	INIT_LIST_HEAD(&sess->cr_inactive_list);
	init_completion(&sess->async_msg_comp);
	init_completion(&sess->reinstatement_comp);
	init_completion(&sess->session_wait_comp);
	init_completion(&sess->session_waiting_on_uc_comp);
	mutex_init(&sess->cmdsn_mutex);
	spin_lock_init(&sess->conn_lock);
	spin_lock_init(&sess->cr_a_lock);
	spin_lock_init(&sess->cr_i_lock);
	spin_lock_init(&sess->session_usage_lock);
	spin_lock_init(&sess->ttt_lock);

	timer_setup(&sess->time2retain_timer,
		    iscsit_handle_time2retain_timeout, 0);

	ret = ida_alloc(&sess_ida, GFP_KERNEL);
	if (ret < 0) {
		pr_err("Session ID allocation failed %d\n", ret);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		goto free_sess;
	}

	sess->session_index = ret;
	sess->creation_time = get_jiffies_64();
	/*
	 * The FFP CmdSN window values will be allocated from the TPG's
	 * Initiator Node's ACL once the login has been successfully completed.
	 */
	atomic_set(&sess->max_cmd_sn, be32_to_cpu(pdu->cmdsn));

	sess->sess_ops = kzalloc(sizeof(struct iscsi_sess_ops), GFP_KERNEL);
	if (!sess->sess_ops) {
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		pr_err("Unable to allocate memory for"
				" struct iscsi_sess_ops.\n");
		goto free_id;
	}

	sess->se_sess = transport_alloc_session(TARGET_PROT_NORMAL);
	if (IS_ERR(sess->se_sess)) {
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		goto free_ops;
	}

	return 0;

free_ops:
	kfree(sess->sess_ops);
free_id:
	ida_free(&sess_ida, sess->session_index);
free_sess:
	kfree(sess);
	conn->sess = NULL;
	return -ENOMEM;
}