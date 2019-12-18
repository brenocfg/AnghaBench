#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qstr {int /*<<< orphan*/  name; int /*<<< orphan*/  len; int /*<<< orphan*/  hash; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_lock; } ;
struct ceph_vino {scalar_t__ ino; scalar_t__ snap; } ;
struct ceph_readdir_cache_control {scalar_t__ index; } ;
struct ceph_mds_session {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  offset_hash; int /*<<< orphan*/  frag; } ;
struct TYPE_15__ {TYPE_5__ readdir; } ;
struct ceph_mds_request_head {TYPE_6__ args; } ;
struct ceph_mds_reply_info_parsed {int dir_nr; scalar_t__ hash_order; struct ceph_mds_reply_dir_entry* dir_entries; TYPE_9__* dir_dir; TYPE_7__* head; scalar_t__ offset_hash; } ;
struct ceph_mds_request {int r_readdir_offset; scalar_t__ r_readdir_cache_idx; int /*<<< orphan*/  r_req_flags; int /*<<< orphan*/  r_request_started; int /*<<< orphan*/  r_session; int /*<<< orphan*/  r_caps_reservation; void* r_dir_ordered_cnt; void* r_dir_release_cnt; int /*<<< orphan*/  r_path2; TYPE_3__* r_request; struct ceph_mds_reply_info_parsed r_reply_info; struct dentry* r_dentry; } ;
struct TYPE_17__ {TYPE_1__* in; } ;
struct ceph_mds_reply_dir_entry {scalar_t__ offset; int /*<<< orphan*/  lease; TYPE_8__ inode; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  dl_dir_hash; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_shared_gen; TYPE_4__ i_dir_layout; int /*<<< orphan*/  i_ordered_count; int /*<<< orphan*/  i_release_count; } ;
struct ceph_dentry_info {scalar_t__ offset; scalar_t__ lease_shared_gen; } ;
struct TYPE_18__ {int /*<<< orphan*/  frag; } ;
struct TYPE_16__ {int /*<<< orphan*/  op; } ;
struct TYPE_11__ {struct ceph_mds_request_head* iov_base; } ;
struct TYPE_12__ {TYPE_2__ front; } ;
struct TYPE_10__ {int /*<<< orphan*/  snapid; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 scalar_t__ CEPH_MDS_OP_LSSNAP ; 
 int /*<<< orphan*/  CEPH_MDS_R_ABORTED ; 
 int /*<<< orphan*/  CEPH_MDS_R_DID_PREPOPULATE ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __ceph_dir_clear_ordered (struct ceph_inode_info*) ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_async_iput (struct inode*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  ceph_fill_dirfrag (struct inode*,TYPE_9__*) ; 
 scalar_t__ ceph_frag_is_leftmost (scalar_t__) ; 
 scalar_t__ ceph_frag_value (scalar_t__) ; 
 struct inode* ceph_get_inode (int /*<<< orphan*/ ,struct ceph_vino) ; 
 scalar_t__ ceph_ino (struct inode*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 void* ceph_make_fpos (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_readdir_cache_release (struct ceph_readdir_cache_control*) ; 
 scalar_t__ ceph_security_xattr_deadlock (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 scalar_t__ ceph_str_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int fill_inode (struct inode*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *,struct ceph_mds_session*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int fill_readdir_cache (struct inode*,struct dentry*,struct ceph_readdir_cache_control*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  full_name_hash (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct inode*) ; 
 int readdir_prepopulate_inodes_only (struct ceph_mds_request*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int splice_dentry (struct dentry**,struct inode*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_dentry_lease (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ceph_readdir_prepopulate(struct ceph_mds_request *req,
			     struct ceph_mds_session *session)
{
	struct dentry *parent = req->r_dentry;
	struct ceph_inode_info *ci = ceph_inode(d_inode(parent));
	struct ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
	struct qstr dname;
	struct dentry *dn;
	struct inode *in;
	int err = 0, skipped = 0, ret, i;
	struct ceph_mds_request_head *rhead = req->r_request->front.iov_base;
	u32 frag = le32_to_cpu(rhead->args.readdir.frag);
	u32 last_hash = 0;
	u32 fpos_offset;
	struct ceph_readdir_cache_control cache_ctl = {};

	if (test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags))
		return readdir_prepopulate_inodes_only(req, session);

	if (rinfo->hash_order) {
		if (req->r_path2) {
			last_hash = ceph_str_hash(ci->i_dir_layout.dl_dir_hash,
						  req->r_path2,
						  strlen(req->r_path2));
			last_hash = ceph_frag_value(last_hash);
		} else if (rinfo->offset_hash) {
			/* mds understands offset_hash */
			WARN_ON_ONCE(req->r_readdir_offset != 2);
			last_hash = le32_to_cpu(rhead->args.readdir.offset_hash);
		}
	}

	if (rinfo->dir_dir &&
	    le32_to_cpu(rinfo->dir_dir->frag) != frag) {
		dout("readdir_prepopulate got new frag %x -> %x\n",
		     frag, le32_to_cpu(rinfo->dir_dir->frag));
		frag = le32_to_cpu(rinfo->dir_dir->frag);
		if (!rinfo->hash_order)
			req->r_readdir_offset = 2;
	}

	if (le32_to_cpu(rinfo->head->op) == CEPH_MDS_OP_LSSNAP) {
		dout("readdir_prepopulate %d items under SNAPDIR dn %p\n",
		     rinfo->dir_nr, parent);
	} else {
		dout("readdir_prepopulate %d items under dn %p\n",
		     rinfo->dir_nr, parent);
		if (rinfo->dir_dir)
			ceph_fill_dirfrag(d_inode(parent), rinfo->dir_dir);

		if (ceph_frag_is_leftmost(frag) &&
		    req->r_readdir_offset == 2 &&
		    !(rinfo->hash_order && last_hash)) {
			/* note dir version at start of readdir so we can
			 * tell if any dentries get dropped */
			req->r_dir_release_cnt =
				atomic64_read(&ci->i_release_count);
			req->r_dir_ordered_cnt =
				atomic64_read(&ci->i_ordered_count);
			req->r_readdir_cache_idx = 0;
		}
	}

	cache_ctl.index = req->r_readdir_cache_idx;
	fpos_offset = req->r_readdir_offset;

	/* FIXME: release caps/leases if error occurs */
	for (i = 0; i < rinfo->dir_nr; i++) {
		struct ceph_mds_reply_dir_entry *rde = rinfo->dir_entries + i;
		struct ceph_vino tvino;

		dname.name = rde->name;
		dname.len = rde->name_len;
		dname.hash = full_name_hash(parent, dname.name, dname.len);

		tvino.ino = le64_to_cpu(rde->inode.in->ino);
		tvino.snap = le64_to_cpu(rde->inode.in->snapid);

		if (rinfo->hash_order) {
			u32 hash = ceph_str_hash(ci->i_dir_layout.dl_dir_hash,
						 rde->name, rde->name_len);
			hash = ceph_frag_value(hash);
			if (hash != last_hash)
				fpos_offset = 2;
			last_hash = hash;
			rde->offset = ceph_make_fpos(hash, fpos_offset++, true);
		} else {
			rde->offset = ceph_make_fpos(frag, fpos_offset++, false);
		}

retry_lookup:
		dn = d_lookup(parent, &dname);
		dout("d_lookup on parent=%p name=%.*s got %p\n",
		     parent, dname.len, dname.name, dn);

		if (!dn) {
			dn = d_alloc(parent, &dname);
			dout("d_alloc %p '%.*s' = %p\n", parent,
			     dname.len, dname.name, dn);
			if (!dn) {
				dout("d_alloc badness\n");
				err = -ENOMEM;
				goto out;
			}
		} else if (d_really_is_positive(dn) &&
			   (ceph_ino(d_inode(dn)) != tvino.ino ||
			    ceph_snap(d_inode(dn)) != tvino.snap)) {
			struct ceph_dentry_info *di = ceph_dentry(dn);
			dout(" dn %p points to wrong inode %p\n",
			     dn, d_inode(dn));

			spin_lock(&dn->d_lock);
			if (di->offset > 0 &&
			    di->lease_shared_gen ==
			    atomic_read(&ci->i_shared_gen)) {
				__ceph_dir_clear_ordered(ci);
				di->offset = 0;
			}
			spin_unlock(&dn->d_lock);

			d_delete(dn);
			dput(dn);
			goto retry_lookup;
		}

		/* inode */
		if (d_really_is_positive(dn)) {
			in = d_inode(dn);
		} else {
			in = ceph_get_inode(parent->d_sb, tvino);
			if (IS_ERR(in)) {
				dout("new_inode badness\n");
				d_drop(dn);
				dput(dn);
				err = PTR_ERR(in);
				goto out;
			}
		}

		ret = fill_inode(in, NULL, &rde->inode, NULL, session,
				 req->r_request_started, -1,
				 &req->r_caps_reservation);
		if (ret < 0) {
			pr_err("fill_inode badness on %p\n", in);
			if (d_really_is_negative(dn)) {
				/* avoid calling iput_final() in mds
				 * dispatch threads */
				ceph_async_iput(in);
			}
			d_drop(dn);
			err = ret;
			goto next_item;
		}

		if (d_really_is_negative(dn)) {
			if (ceph_security_xattr_deadlock(in)) {
				dout(" skip splicing dn %p to inode %p"
				     " (security xattr deadlock)\n", dn, in);
				ceph_async_iput(in);
				skipped++;
				goto next_item;
			}

			err = splice_dentry(&dn, in);
			if (err < 0)
				goto next_item;
		}

		ceph_dentry(dn)->offset = rde->offset;

		update_dentry_lease(d_inode(parent), dn,
				    rde->lease, req->r_session,
				    req->r_request_started);

		if (err == 0 && skipped == 0 && cache_ctl.index >= 0) {
			ret = fill_readdir_cache(d_inode(parent), dn,
						 &cache_ctl, req);
			if (ret < 0)
				err = ret;
		}
next_item:
		dput(dn);
	}
out:
	if (err == 0 && skipped == 0) {
		set_bit(CEPH_MDS_R_DID_PREPOPULATE, &req->r_req_flags);
		req->r_readdir_cache_idx = cache_ctl.index;
	}
	ceph_readdir_cache_release(&cache_ctl);
	dout("readdir_prepopulate done\n");
	return err;
}