#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iscsi_session {int /*<<< orphan*/  session_wait_comp; int /*<<< orphan*/  sleep_on_sess_wait_comp; int /*<<< orphan*/  conn_lock; int /*<<< orphan*/  session_continuation; int /*<<< orphan*/  session_state; int /*<<< orphan*/  session_logout; int /*<<< orphan*/  session_fall_back_to_erl0; int /*<<< orphan*/  session_reinstatement; int /*<<< orphan*/  session_stop_active; int /*<<< orphan*/  nconn; TYPE_1__* sess_ops; int /*<<< orphan*/  sid; } ;
struct iscsi_conn {scalar_t__ conn_state; scalar_t__ conn_logout_reason; TYPE_2__* conn_transport; scalar_t__ sock; scalar_t__ conn_rx_hash; scalar_t__ conn_tx_hash; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  connection_reinstatement; int /*<<< orphan*/  conn_post_wait_comp; int /*<<< orphan*/  conn_wait_rcfr_comp; int /*<<< orphan*/  connection_wait_rcfr; int /*<<< orphan*/  conn_wait_comp; int /*<<< orphan*/  sleep_on_conn_wait_comp; int /*<<< orphan*/  connection_recovery; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  conn_logout_remove; int /*<<< orphan*/  bitmap_id; scalar_t__ rx_thread; int /*<<< orphan*/  rx_thread_active; scalar_t__ tx_thread; int /*<<< orphan*/  tx_thread_active; int /*<<< orphan*/  conn_logout_comp; int /*<<< orphan*/  cid; struct iscsi_session* sess; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  comm; } ;
struct TYPE_7__ {int /*<<< orphan*/  ts_bitmap_lock; int /*<<< orphan*/  ts_bitmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* iscsit_free_conn ) (struct iscsi_conn*) ;int /*<<< orphan*/  (* iscsit_wait_conn ) (struct iscsi_conn*) ;int /*<<< orphan*/  rdma_shutdown; } ;
struct TYPE_5__ {int ErrorRecoveryLevel; int /*<<< orphan*/  InitiatorName; } ;

/* Variables and functions */
 scalar_t__ ISCSI_LOGOUT_REASON_CLOSE_CONNECTION ; 
 scalar_t__ ISCSI_LOGOUT_REASON_CLOSE_SESSION ; 
 int /*<<< orphan*/  ISCSI_RX_THREAD_NAME ; 
 int /*<<< orphan*/  ISCSI_TX_THREAD_NAME ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ TARG_CONN_STATE_FREE ; 
 scalar_t__ TARG_CONN_STATE_IN_LOGOUT ; 
 int /*<<< orphan*/  TARG_SESS_STATE_FAILED ; 
 int /*<<< orphan*/  TARG_SESS_STATE_FREE ; 
 int /*<<< orphan*/  ahash_request_free (scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  iscsit_build_conn_drop_async_message (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_check_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_clear_ooo_cmdsns_for_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_close_session (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsit_dec_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_dec_session_usage_count (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsit_discard_unacknowledged_ooo_cmdsns_for_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_free_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_free_queue_reqs_for_conn (struct iscsi_conn*) ; 
 TYPE_3__* iscsit_global ; 
 int /*<<< orphan*/  iscsit_prepare_cmds_for_reallegiance (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_release_commands_from_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_start_time2retain_handler (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsit_stop_nopin_response_timer (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_stop_nopin_timer (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_stop_session (struct iscsi_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_stop_timers_for_cmds (struct iscsi_conn*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sock_release (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_conn*) ; 
 int /*<<< orphan*/  stub2 (struct iscsi_conn*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int iscsit_close_connection(
	struct iscsi_conn *conn)
{
	int conn_logout = (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT);
	struct iscsi_session	*sess = conn->sess;

	pr_debug("Closing iSCSI connection CID %hu on SID:"
		" %u\n", conn->cid, sess->sid);
	/*
	 * Always up conn_logout_comp for the traditional TCP and HW_OFFLOAD
	 * case just in case the RX Thread in iscsi_target_rx_opcode() is
	 * sleeping and the logout response never got sent because the
	 * connection failed.
	 *
	 * However for iser-target, isert_wait4logout() is using conn_logout_comp
	 * to signal logout response TX interrupt completion.  Go ahead and skip
	 * this for iser since isert_rx_opcode() does not wait on logout failure,
	 * and to avoid iscsi_conn pointer dereference in iser-target code.
	 */
	if (!conn->conn_transport->rdma_shutdown)
		complete(&conn->conn_logout_comp);

	if (!strcmp(current->comm, ISCSI_RX_THREAD_NAME)) {
		if (conn->tx_thread &&
		    cmpxchg(&conn->tx_thread_active, true, false)) {
			send_sig(SIGINT, conn->tx_thread, 1);
			kthread_stop(conn->tx_thread);
		}
	} else if (!strcmp(current->comm, ISCSI_TX_THREAD_NAME)) {
		if (conn->rx_thread &&
		    cmpxchg(&conn->rx_thread_active, true, false)) {
			send_sig(SIGINT, conn->rx_thread, 1);
			kthread_stop(conn->rx_thread);
		}
	}

	spin_lock(&iscsit_global->ts_bitmap_lock);
	bitmap_release_region(iscsit_global->ts_bitmap, conn->bitmap_id,
			      get_order(1));
	spin_unlock(&iscsit_global->ts_bitmap_lock);

	iscsit_stop_timers_for_cmds(conn);
	iscsit_stop_nopin_response_timer(conn);
	iscsit_stop_nopin_timer(conn);

	if (conn->conn_transport->iscsit_wait_conn)
		conn->conn_transport->iscsit_wait_conn(conn);

	/*
	 * During Connection recovery drop unacknowledged out of order
	 * commands for this connection, and prepare the other commands
	 * for reallegiance.
	 *
	 * During normal operation clear the out of order commands (but
	 * do not free the struct iscsi_ooo_cmdsn's) and release all
	 * struct iscsi_cmds.
	 */
	if (atomic_read(&conn->connection_recovery)) {
		iscsit_discard_unacknowledged_ooo_cmdsns_for_conn(conn);
		iscsit_prepare_cmds_for_reallegiance(conn);
	} else {
		iscsit_clear_ooo_cmdsns_for_conn(conn);
		iscsit_release_commands_from_conn(conn);
	}
	iscsit_free_queue_reqs_for_conn(conn);

	/*
	 * Handle decrementing session or connection usage count if
	 * a logout response was not able to be sent because the
	 * connection failed.  Fall back to Session Recovery here.
	 */
	if (atomic_read(&conn->conn_logout_remove)) {
		if (conn->conn_logout_reason == ISCSI_LOGOUT_REASON_CLOSE_SESSION) {
			iscsit_dec_conn_usage_count(conn);
			iscsit_dec_session_usage_count(sess);
		}
		if (conn->conn_logout_reason == ISCSI_LOGOUT_REASON_CLOSE_CONNECTION)
			iscsit_dec_conn_usage_count(conn);

		atomic_set(&conn->conn_logout_remove, 0);
		atomic_set(&sess->session_reinstatement, 0);
		atomic_set(&sess->session_fall_back_to_erl0, 1);
	}

	spin_lock_bh(&sess->conn_lock);
	list_del(&conn->conn_list);

	/*
	 * Attempt to let the Initiator know this connection failed by
	 * sending an Connection Dropped Async Message on another
	 * active connection.
	 */
	if (atomic_read(&conn->connection_recovery))
		iscsit_build_conn_drop_async_message(conn);

	spin_unlock_bh(&sess->conn_lock);

	/*
	 * If connection reinstatement is being performed on this connection,
	 * up the connection reinstatement semaphore that is being blocked on
	 * in iscsit_cause_connection_reinstatement().
	 */
	spin_lock_bh(&conn->state_lock);
	if (atomic_read(&conn->sleep_on_conn_wait_comp)) {
		spin_unlock_bh(&conn->state_lock);
		complete(&conn->conn_wait_comp);
		wait_for_completion(&conn->conn_post_wait_comp);
		spin_lock_bh(&conn->state_lock);
	}

	/*
	 * If connection reinstatement is being performed on this connection
	 * by receiving a REMOVECONNFORRECOVERY logout request, up the
	 * connection wait rcfr semaphore that is being blocked on
	 * an iscsit_connection_reinstatement_rcfr().
	 */
	if (atomic_read(&conn->connection_wait_rcfr)) {
		spin_unlock_bh(&conn->state_lock);
		complete(&conn->conn_wait_rcfr_comp);
		wait_for_completion(&conn->conn_post_wait_comp);
		spin_lock_bh(&conn->state_lock);
	}
	atomic_set(&conn->connection_reinstatement, 1);
	spin_unlock_bh(&conn->state_lock);

	/*
	 * If any other processes are accessing this connection pointer we
	 * must wait until they have completed.
	 */
	iscsit_check_conn_usage_count(conn);

	ahash_request_free(conn->conn_tx_hash);
	if (conn->conn_rx_hash) {
		struct crypto_ahash *tfm;

		tfm = crypto_ahash_reqtfm(conn->conn_rx_hash);
		ahash_request_free(conn->conn_rx_hash);
		crypto_free_ahash(tfm);
	}

	if (conn->sock)
		sock_release(conn->sock);

	if (conn->conn_transport->iscsit_free_conn)
		conn->conn_transport->iscsit_free_conn(conn);

	pr_debug("Moving to TARG_CONN_STATE_FREE.\n");
	conn->conn_state = TARG_CONN_STATE_FREE;
	iscsit_free_conn(conn);

	spin_lock_bh(&sess->conn_lock);
	atomic_dec(&sess->nconn);
	pr_debug("Decremented iSCSI connection count to %hu from node:"
		" %s\n", atomic_read(&sess->nconn),
		sess->sess_ops->InitiatorName);
	/*
	 * Make sure that if one connection fails in an non ERL=2 iSCSI
	 * Session that they all fail.
	 */
	if ((sess->sess_ops->ErrorRecoveryLevel != 2) && !conn_logout &&
	     !atomic_read(&sess->session_logout))
		atomic_set(&sess->session_fall_back_to_erl0, 1);

	/*
	 * If this was not the last connection in the session, and we are
	 * performing session reinstatement or falling back to ERL=0, call
	 * iscsit_stop_session() without sleeping to shutdown the other
	 * active connections.
	 */
	if (atomic_read(&sess->nconn)) {
		if (!atomic_read(&sess->session_reinstatement) &&
		    !atomic_read(&sess->session_fall_back_to_erl0)) {
			spin_unlock_bh(&sess->conn_lock);
			return 0;
		}
		if (!atomic_read(&sess->session_stop_active)) {
			atomic_set(&sess->session_stop_active, 1);
			spin_unlock_bh(&sess->conn_lock);
			iscsit_stop_session(sess, 0, 0);
			return 0;
		}
		spin_unlock_bh(&sess->conn_lock);
		return 0;
	}

	/*
	 * If this was the last connection in the session and one of the
	 * following is occurring:
	 *
	 * Session Reinstatement is not being performed, and are falling back
	 * to ERL=0 call iscsit_close_session().
	 *
	 * Session Logout was requested.  iscsit_close_session() will be called
	 * elsewhere.
	 *
	 * Session Continuation is not being performed, start the Time2Retain
	 * handler and check if sleep_on_sess_wait_sem is active.
	 */
	if (!atomic_read(&sess->session_reinstatement) &&
	     atomic_read(&sess->session_fall_back_to_erl0)) {
		spin_unlock_bh(&sess->conn_lock);
		iscsit_close_session(sess);

		return 0;
	} else if (atomic_read(&sess->session_logout)) {
		pr_debug("Moving to TARG_SESS_STATE_FREE.\n");
		sess->session_state = TARG_SESS_STATE_FREE;
		spin_unlock_bh(&sess->conn_lock);

		if (atomic_read(&sess->sleep_on_sess_wait_comp))
			complete(&sess->session_wait_comp);

		return 0;
	} else {
		pr_debug("Moving to TARG_SESS_STATE_FAILED.\n");
		sess->session_state = TARG_SESS_STATE_FAILED;

		if (!atomic_read(&sess->session_continuation)) {
			spin_unlock_bh(&sess->conn_lock);
			iscsit_start_time2retain_handler(sess);
		} else
			spin_unlock_bh(&sess->conn_lock);

		if (atomic_read(&sess->sleep_on_sess_wait_comp))
			complete(&sess->session_wait_comp);

		return 0;
	}
}