#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  struct ceph_mds_request* u64 ;
struct ceph_snap_realm {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  tid; } ;
struct TYPE_8__ {int iov_len; struct ceph_mds_reply_head* iov_base; } ;
struct ceph_msg {TYPE_4__ hdr; TYPE_3__ front; } ;
struct TYPE_6__ {struct ceph_mds_request* peer_features; } ;
struct ceph_mds_session {int s_mds; int /*<<< orphan*/  s_mutex; TYPE_1__ s_con; int /*<<< orphan*/  s_features; int /*<<< orphan*/  s_unsafe; struct ceph_mds_client* s_mdsc; } ;
struct ceph_mds_reply_info_parsed {scalar_t__ snapblob_len; scalar_t__ snapblob; } ;
struct ceph_mds_request {int r_resend_mds; scalar_t__ r_direct_mode; scalar_t__ r_op; int r_err; int /*<<< orphan*/  r_req_flags; int /*<<< orphan*/  r_reply; int /*<<< orphan*/  r_caps_reservation; int /*<<< orphan*/  r_unsafe_target_item; scalar_t__ r_target_inode; int /*<<< orphan*/  r_fill_mutex; struct ceph_mds_session* r_session; struct ceph_mds_reply_info_parsed r_reply_info; int /*<<< orphan*/  r_unsafe_dir_item; scalar_t__ r_unsafe_dir; int /*<<< orphan*/  r_unsafe_item; struct ceph_mds_request* r_tid; } ;
struct ceph_mds_reply_head {int /*<<< orphan*/  op; scalar_t__ safe; int /*<<< orphan*/  result; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; int /*<<< orphan*/  snap_rwsem; TYPE_2__* fsc; int /*<<< orphan*/  safe_umount_waiters; scalar_t__ stopping; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_unsafe_lock; int /*<<< orphan*/  i_unsafe_iops; int /*<<< orphan*/  i_unsafe_dirops; } ;
struct TYPE_10__ {struct ceph_mds_request* journal_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPHFS_FEATURE_REPLY_ENCODING ; 
 scalar_t__ CEPH_MDS_OP_LSSNAP ; 
 scalar_t__ CEPH_MDS_OP_READDIR ; 
 int CEPH_MDS_OP_RMSNAP ; 
 int /*<<< orphan*/  CEPH_MDS_R_ABORTED ; 
 int /*<<< orphan*/  CEPH_MDS_R_GOT_RESULT ; 
 int /*<<< orphan*/  CEPH_MDS_R_GOT_SAFE ; 
 int /*<<< orphan*/  CEPH_MDS_R_GOT_UNSAFE ; 
 int ESTALE ; 
 scalar_t__ USE_AUTH_MDS ; 
 int __choose_mds (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __do_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __get_oldest_req (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  __unregister_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int ceph_fill_trace (int /*<<< orphan*/ ,struct ceph_mds_request*) ; 
 struct ceph_inode_info* ceph_inode (scalar_t__) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_msg_dump (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_get (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_put_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 int /*<<< orphan*/  ceph_readdir_prepopulate (struct ceph_mds_request*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_unreserve_caps (struct ceph_mds_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_update_snap_trace (struct ceph_mds_client*,scalar_t__,scalar_t__,int,struct ceph_snap_realm**) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ceph_mds_request* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ceph_mds_request* lookup_get_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_reply_info (struct ceph_msg*,struct ceph_mds_reply_info_parsed*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_reply(struct ceph_mds_session *session, struct ceph_msg *msg)
{
	struct ceph_mds_client *mdsc = session->s_mdsc;
	struct ceph_mds_request *req;
	struct ceph_mds_reply_head *head = msg->front.iov_base;
	struct ceph_mds_reply_info_parsed *rinfo;  /* parsed reply info */
	struct ceph_snap_realm *realm;
	u64 tid;
	int err, result;
	int mds = session->s_mds;

	if (msg->front.iov_len < sizeof(*head)) {
		pr_err("mdsc_handle_reply got corrupt (short) reply\n");
		ceph_msg_dump(msg);
		return;
	}

	/* get request, session */
	tid = le64_to_cpu(msg->hdr.tid);
	mutex_lock(&mdsc->mutex);
	req = lookup_get_request(mdsc, tid);
	if (!req) {
		dout("handle_reply on unknown tid %llu\n", tid);
		mutex_unlock(&mdsc->mutex);
		return;
	}
	dout("handle_reply %p\n", req);

	/* correct session? */
	if (req->r_session != session) {
		pr_err("mdsc_handle_reply got %llu on session mds%d"
		       " not mds%d\n", tid, session->s_mds,
		       req->r_session ? req->r_session->s_mds : -1);
		mutex_unlock(&mdsc->mutex);
		goto out;
	}

	/* dup? */
	if ((test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags) && !head->safe) ||
	    (test_bit(CEPH_MDS_R_GOT_SAFE, &req->r_req_flags) && head->safe)) {
		pr_warn("got a dup %s reply on %llu from mds%d\n",
			   head->safe ? "safe" : "unsafe", tid, mds);
		mutex_unlock(&mdsc->mutex);
		goto out;
	}
	if (test_bit(CEPH_MDS_R_GOT_SAFE, &req->r_req_flags)) {
		pr_warn("got unsafe after safe on %llu from mds%d\n",
			   tid, mds);
		mutex_unlock(&mdsc->mutex);
		goto out;
	}

	result = le32_to_cpu(head->result);

	/*
	 * Handle an ESTALE
	 * if we're not talking to the authority, send to them
	 * if the authority has changed while we weren't looking,
	 * send to new authority
	 * Otherwise we just have to return an ESTALE
	 */
	if (result == -ESTALE) {
		dout("got ESTALE on request %llu\n", req->r_tid);
		req->r_resend_mds = -1;
		if (req->r_direct_mode != USE_AUTH_MDS) {
			dout("not using auth, setting for that now\n");
			req->r_direct_mode = USE_AUTH_MDS;
			__do_request(mdsc, req);
			mutex_unlock(&mdsc->mutex);
			goto out;
		} else  {
			int mds = __choose_mds(mdsc, req);
			if (mds >= 0 && mds != req->r_session->s_mds) {
				dout("but auth changed, so resending\n");
				__do_request(mdsc, req);
				mutex_unlock(&mdsc->mutex);
				goto out;
			}
		}
		dout("have to return ESTALE on request %llu\n", req->r_tid);
	}


	if (head->safe) {
		set_bit(CEPH_MDS_R_GOT_SAFE, &req->r_req_flags);
		__unregister_request(mdsc, req);

		if (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags)) {
			/*
			 * We already handled the unsafe response, now do the
			 * cleanup.  No need to examine the response; the MDS
			 * doesn't include any result info in the safe
			 * response.  And even if it did, there is nothing
			 * useful we could do with a revised return value.
			 */
			dout("got safe reply %llu, mds%d\n", tid, mds);

			/* last unsafe request during umount? */
			if (mdsc->stopping && !__get_oldest_req(mdsc))
				complete_all(&mdsc->safe_umount_waiters);
			mutex_unlock(&mdsc->mutex);
			goto out;
		}
	} else {
		set_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags);
		list_add_tail(&req->r_unsafe_item, &req->r_session->s_unsafe);
		if (req->r_unsafe_dir) {
			struct ceph_inode_info *ci =
					ceph_inode(req->r_unsafe_dir);
			spin_lock(&ci->i_unsafe_lock);
			list_add_tail(&req->r_unsafe_dir_item,
				      &ci->i_unsafe_dirops);
			spin_unlock(&ci->i_unsafe_lock);
		}
	}

	dout("handle_reply tid %lld result %d\n", tid, result);
	rinfo = &req->r_reply_info;
	if (test_bit(CEPHFS_FEATURE_REPLY_ENCODING, &session->s_features))
		err = parse_reply_info(msg, rinfo, (u64)-1);
	else
		err = parse_reply_info(msg, rinfo, session->s_con.peer_features);
	mutex_unlock(&mdsc->mutex);

	mutex_lock(&session->s_mutex);
	if (err < 0) {
		pr_err("mdsc_handle_reply got corrupt reply mds%d(tid:%lld)\n", mds, tid);
		ceph_msg_dump(msg);
		goto out_err;
	}

	/* snap trace */
	realm = NULL;
	if (rinfo->snapblob_len) {
		down_write(&mdsc->snap_rwsem);
		ceph_update_snap_trace(mdsc, rinfo->snapblob,
				rinfo->snapblob + rinfo->snapblob_len,
				le32_to_cpu(head->op) == CEPH_MDS_OP_RMSNAP,
				&realm);
		downgrade_write(&mdsc->snap_rwsem);
	} else {
		down_read(&mdsc->snap_rwsem);
	}

	/* insert trace into our cache */
	mutex_lock(&req->r_fill_mutex);
	current->journal_info = req;
	err = ceph_fill_trace(mdsc->fsc->sb, req);
	if (err == 0) {
		if (result == 0 && (req->r_op == CEPH_MDS_OP_READDIR ||
				    req->r_op == CEPH_MDS_OP_LSSNAP))
			ceph_readdir_prepopulate(req, req->r_session);
	}
	current->journal_info = NULL;
	mutex_unlock(&req->r_fill_mutex);

	up_read(&mdsc->snap_rwsem);
	if (realm)
		ceph_put_snap_realm(mdsc, realm);

	if (err == 0) {
		if (req->r_target_inode &&
		    test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags)) {
			struct ceph_inode_info *ci =
				ceph_inode(req->r_target_inode);
			spin_lock(&ci->i_unsafe_lock);
			list_add_tail(&req->r_unsafe_target_item,
				      &ci->i_unsafe_iops);
			spin_unlock(&ci->i_unsafe_lock);
		}

		ceph_unreserve_caps(mdsc, &req->r_caps_reservation);
	}
out_err:
	mutex_lock(&mdsc->mutex);
	if (!test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags)) {
		if (err) {
			req->r_err = err;
		} else {
			req->r_reply =  ceph_msg_get(msg);
			set_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags);
		}
	} else {
		dout("reply arrived after request %lld was aborted\n", tid);
	}
	mutex_unlock(&mdsc->mutex);

	mutex_unlock(&session->s_mutex);

	/* kick calling process */
	complete_request(mdsc, req);
out:
	ceph_mdsc_put_request(req);
	return;
}