#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct inode {scalar_t__ i_sb; int /*<<< orphan*/  i_mapping; } ;
struct file {int dummy; } ;
struct ceph_object_locator {void* pool_ns; int /*<<< orphan*/  pool; } ;
struct ceph_object_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  snap; int /*<<< orphan*/  ino; } ;
struct TYPE_6__ {scalar_t__ stripe_unit; int stripe_count; size_t object_size; int /*<<< orphan*/  pool_ns; int /*<<< orphan*/  pool_id; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/  i_inline_version; TYPE_1__ i_vino; TYPE_3__ i_layout; } ;
struct ceph_fs_client {TYPE_2__* client; } ;
struct ceph_cap_flush {int dummy; } ;
typedef  int ssize_t ;
typedef  size_t loff_t ;
struct TYPE_5__ {int /*<<< orphan*/  osdc; int /*<<< orphan*/  fsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_FILE_WR ; 
 int /*<<< orphan*/  CEPH_INLINE_NONE ; 
 scalar_t__ CEPH_NOSNAP ; 
 int CEPH_OSD_OP_FLAG_FADVISE_DONTNEED ; 
 int CEPH_OSD_OP_FLAG_FADVISE_NOCACHE ; 
 int CEPH_OSD_OP_FLAG_FADVISE_SEQUENTIAL ; 
 int CHECK_CAPS_AUTHONLY ; 
 int CHECK_CAPS_NODELAY ; 
 int /*<<< orphan*/  EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 int EXDEV ; 
 int /*<<< orphan*/  NOCOPYFROM ; 
 size_t PAGE_SHIFT ; 
 int __ceph_mark_dirty_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,struct ceph_cap_flush**) ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int) ; 
 struct ceph_cap_flush* ceph_alloc_cap_flush () ; 
 int /*<<< orphan*/  ceph_calc_file_object_mapping (TYPE_3__*,size_t,size_t,scalar_t__*,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_free_cap_flush (struct ceph_cap_flush*) ; 
 scalar_t__ ceph_fsid_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 scalar_t__ ceph_inode_set_size (struct inode*,size_t) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  ceph_oid_init (struct ceph_object_id*) ; 
 int /*<<< orphan*/  ceph_oid_printf (struct ceph_object_id*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ceph_osdc_copy_from (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ceph_object_id*,struct ceph_object_locator*,int,struct ceph_object_id*,struct ceph_object_locator*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_quota_is_max_bytes_approaching (struct inode*,size_t) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 scalar_t__ ceph_test_mount_opt (struct ceph_fs_client*,int /*<<< orphan*/ ) ; 
 void* ceph_try_get_string (int /*<<< orphan*/ ) ; 
 int do_splice_direct (struct file*,size_t*,struct file*,size_t*,size_t,unsigned int) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int file_write_and_wait_range (struct file*,size_t,size_t) ; 
 int get_rd_wr_caps (struct file*,int*,struct file*,size_t,int*) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion_raw (struct inode*) ; 
 int invalidate_inode_pages2_range (int /*<<< orphan*/ ,size_t,size_t) ; 
 int is_file_size_ok (struct inode*,struct inode*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  put_rd_wr_caps (struct ceph_inode_info*,int,struct ceph_inode_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __ceph_copy_file_range(struct file *src_file, loff_t src_off,
				      struct file *dst_file, loff_t dst_off,
				      size_t len, unsigned int flags)
{
	struct inode *src_inode = file_inode(src_file);
	struct inode *dst_inode = file_inode(dst_file);
	struct ceph_inode_info *src_ci = ceph_inode(src_inode);
	struct ceph_inode_info *dst_ci = ceph_inode(dst_inode);
	struct ceph_cap_flush *prealloc_cf;
	struct ceph_fs_client *src_fsc = ceph_inode_to_client(src_inode);
	struct ceph_object_locator src_oloc, dst_oloc;
	struct ceph_object_id src_oid, dst_oid;
	loff_t endoff = 0, size;
	ssize_t ret = -EIO;
	u64 src_objnum, dst_objnum, src_objoff, dst_objoff;
	u32 src_objlen, dst_objlen, object_size;
	int src_got = 0, dst_got = 0, err, dirty;
	bool do_final_copy = false;

	if (src_inode->i_sb != dst_inode->i_sb) {
		struct ceph_fs_client *dst_fsc = ceph_inode_to_client(dst_inode);

		if (ceph_fsid_compare(&src_fsc->client->fsid,
				      &dst_fsc->client->fsid)) {
			dout("Copying files across clusters: src: %pU dst: %pU\n",
			     &src_fsc->client->fsid, &dst_fsc->client->fsid);
			return -EXDEV;
		}
	}
	if (ceph_snap(dst_inode) != CEPH_NOSNAP)
		return -EROFS;

	/*
	 * Some of the checks below will return -EOPNOTSUPP, which will force a
	 * fallback to the default VFS copy_file_range implementation.  This is
	 * desirable in several cases (for ex, the 'len' is smaller than the
	 * size of the objects, or in cases where that would be more
	 * efficient).
	 */

	if (ceph_test_mount_opt(src_fsc, NOCOPYFROM))
		return -EOPNOTSUPP;

	/*
	 * Striped file layouts require that we copy partial objects, but the
	 * OSD copy-from operation only supports full-object copies.  Limit
	 * this to non-striped file layouts for now.
	 */
	if ((src_ci->i_layout.stripe_unit != dst_ci->i_layout.stripe_unit) ||
	    (src_ci->i_layout.stripe_count != 1) ||
	    (dst_ci->i_layout.stripe_count != 1) ||
	    (src_ci->i_layout.object_size != dst_ci->i_layout.object_size)) {
		dout("Invalid src/dst files layout\n");
		return -EOPNOTSUPP;
	}

	if (len < src_ci->i_layout.object_size)
		return -EOPNOTSUPP; /* no remote copy will be done */

	prealloc_cf = ceph_alloc_cap_flush();
	if (!prealloc_cf)
		return -ENOMEM;

	/* Start by sync'ing the source and destination files */
	ret = file_write_and_wait_range(src_file, src_off, (src_off + len));
	if (ret < 0) {
		dout("failed to write src file (%zd)\n", ret);
		goto out;
	}
	ret = file_write_and_wait_range(dst_file, dst_off, (dst_off + len));
	if (ret < 0) {
		dout("failed to write dst file (%zd)\n", ret);
		goto out;
	}

	/*
	 * We need FILE_WR caps for dst_ci and FILE_RD for src_ci as other
	 * clients may have dirty data in their caches.  And OSDs know nothing
	 * about caps, so they can't safely do the remote object copies.
	 */
	err = get_rd_wr_caps(src_file, &src_got,
			     dst_file, (dst_off + len), &dst_got);
	if (err < 0) {
		dout("get_rd_wr_caps returned %d\n", err);
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = is_file_size_ok(src_inode, dst_inode, src_off, dst_off, len);
	if (ret < 0)
		goto out_caps;

	size = i_size_read(dst_inode);
	endoff = dst_off + len;

	/* Drop dst file cached pages */
	ret = invalidate_inode_pages2_range(dst_inode->i_mapping,
					    dst_off >> PAGE_SHIFT,
					    endoff >> PAGE_SHIFT);
	if (ret < 0) {
		dout("Failed to invalidate inode pages (%zd)\n", ret);
		ret = 0; /* XXX */
	}
	src_oloc.pool = src_ci->i_layout.pool_id;
	src_oloc.pool_ns = ceph_try_get_string(src_ci->i_layout.pool_ns);
	dst_oloc.pool = dst_ci->i_layout.pool_id;
	dst_oloc.pool_ns = ceph_try_get_string(dst_ci->i_layout.pool_ns);

	ceph_calc_file_object_mapping(&src_ci->i_layout, src_off,
				      src_ci->i_layout.object_size,
				      &src_objnum, &src_objoff, &src_objlen);
	ceph_calc_file_object_mapping(&dst_ci->i_layout, dst_off,
				      dst_ci->i_layout.object_size,
				      &dst_objnum, &dst_objoff, &dst_objlen);
	/* object-level offsets need to the same */
	if (src_objoff != dst_objoff) {
		ret = -EOPNOTSUPP;
		goto out_caps;
	}

	/*
	 * Do a manual copy if the object offset isn't object aligned.
	 * 'src_objlen' contains the bytes left until the end of the object,
	 * starting at the src_off
	 */
	if (src_objoff) {
		/*
		 * we need to temporarily drop all caps as we'll be calling
		 * {read,write}_iter, which will get caps again.
		 */
		put_rd_wr_caps(src_ci, src_got, dst_ci, dst_got);
		ret = do_splice_direct(src_file, &src_off, dst_file,
				       &dst_off, src_objlen, flags);
		if (ret < 0) {
			dout("do_splice_direct returned %d\n", err);
			goto out;
		}
		len -= ret;
		err = get_rd_wr_caps(src_file, &src_got,
				     dst_file, (dst_off + len), &dst_got);
		if (err < 0)
			goto out;
		err = is_file_size_ok(src_inode, dst_inode,
				      src_off, dst_off, len);
		if (err < 0)
			goto out_caps;
	}
	object_size = src_ci->i_layout.object_size;
	while (len >= object_size) {
		ceph_calc_file_object_mapping(&src_ci->i_layout, src_off,
					      object_size, &src_objnum,
					      &src_objoff, &src_objlen);
		ceph_calc_file_object_mapping(&dst_ci->i_layout, dst_off,
					      object_size, &dst_objnum,
					      &dst_objoff, &dst_objlen);
		ceph_oid_init(&src_oid);
		ceph_oid_printf(&src_oid, "%llx.%08llx",
				src_ci->i_vino.ino, src_objnum);
		ceph_oid_init(&dst_oid);
		ceph_oid_printf(&dst_oid, "%llx.%08llx",
				dst_ci->i_vino.ino, dst_objnum);
		/* Do an object remote copy */
		err = ceph_osdc_copy_from(
			&src_fsc->client->osdc,
			src_ci->i_vino.snap, 0,
			&src_oid, &src_oloc,
			CEPH_OSD_OP_FLAG_FADVISE_SEQUENTIAL |
			CEPH_OSD_OP_FLAG_FADVISE_NOCACHE,
			&dst_oid, &dst_oloc,
			CEPH_OSD_OP_FLAG_FADVISE_SEQUENTIAL |
			CEPH_OSD_OP_FLAG_FADVISE_DONTNEED, 0);
		if (err) {
			dout("ceph_osdc_copy_from returned %d\n", err);
			if (!ret)
				ret = err;
			goto out_caps;
		}
		len -= object_size;
		src_off += object_size;
		dst_off += object_size;
		ret += object_size;
	}

	if (len)
		/* We still need one final local copy */
		do_final_copy = true;

	file_update_time(dst_file);
	inode_inc_iversion_raw(dst_inode);

	if (endoff > size) {
		int caps_flags = 0;

		/* Let the MDS know about dst file size change */
		if (ceph_quota_is_max_bytes_approaching(dst_inode, endoff))
			caps_flags |= CHECK_CAPS_NODELAY;
		if (ceph_inode_set_size(dst_inode, endoff))
			caps_flags |= CHECK_CAPS_AUTHONLY;
		if (caps_flags)
			ceph_check_caps(dst_ci, caps_flags, NULL);
	}
	/* Mark Fw dirty */
	spin_lock(&dst_ci->i_ceph_lock);
	dst_ci->i_inline_version = CEPH_INLINE_NONE;
	dirty = __ceph_mark_dirty_caps(dst_ci, CEPH_CAP_FILE_WR, &prealloc_cf);
	spin_unlock(&dst_ci->i_ceph_lock);
	if (dirty)
		__mark_inode_dirty(dst_inode, dirty);

out_caps:
	put_rd_wr_caps(src_ci, src_got, dst_ci, dst_got);

	if (do_final_copy) {
		err = do_splice_direct(src_file, &src_off, dst_file,
				       &dst_off, len, flags);
		if (err < 0) {
			dout("do_splice_direct returned %d\n", err);
			goto out;
		}
		len -= err;
		ret += err;
	}

out:
	ceph_free_cap_flush(prealloc_cf);

	return ret;
}