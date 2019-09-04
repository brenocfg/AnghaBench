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
typedef  int u64 ;
struct TYPE_10__ {int* val; } ;
struct kstatfs {int f_bsize; int f_frsize; int f_blocks; int f_bfree; int f_bavail; int f_files; int f_ffree; TYPE_5__ f_fsid; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_type; } ;
struct dentry {int dummy; } ;
struct ceph_statfs {int /*<<< orphan*/  num_objects; int /*<<< orphan*/  kb_avail; int /*<<< orphan*/  kb; } ;
struct ceph_mon_client {int /*<<< orphan*/  mutex; TYPE_4__* monmap; } ;
struct ceph_fs_client {TYPE_3__* mdsc; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_9__ {int /*<<< orphan*/  fsid; } ;
struct TYPE_8__ {TYPE_2__* mdsmap; } ;
struct TYPE_7__ {int m_num_data_pg_pools; int* m_data_pg_pools; } ;
struct TYPE_6__ {struct ceph_mon_client monc; } ;

/* Variables and functions */
 int CEPH_BLOCK_SHIFT ; 
 int CEPH_NOPOOL ; 
 int /*<<< orphan*/  CEPH_SUPER_MAGIC ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  NOQUOTADF ; 
 struct ceph_fs_client* ceph_inode_to_client (int /*<<< orphan*/ ) ; 
 int ceph_monc_do_statfs (struct ceph_mon_client*,int,struct ceph_statfs*) ; 
 int /*<<< orphan*/  ceph_quota_update_statfs (struct ceph_fs_client*,struct kstatfs*) ; 
 scalar_t__ ceph_test_mount_opt (struct ceph_fs_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct ceph_fs_client *fsc = ceph_inode_to_client(d_inode(dentry));
	struct ceph_mon_client *monc = &fsc->client->monc;
	struct ceph_statfs st;
	u64 fsid;
	int err;
	u64 data_pool;

	if (fsc->mdsc->mdsmap->m_num_data_pg_pools == 1) {
		data_pool = fsc->mdsc->mdsmap->m_data_pg_pools[0];
	} else {
		data_pool = CEPH_NOPOOL;
	}

	dout("statfs\n");
	err = ceph_monc_do_statfs(monc, data_pool, &st);
	if (err < 0)
		return err;

	/* fill in kstatfs */
	buf->f_type = CEPH_SUPER_MAGIC;  /* ?? */

	/*
	 * express utilization in terms of large blocks to avoid
	 * overflow on 32-bit machines.
	 *
	 * NOTE: for the time being, we make bsize == frsize to humor
	 * not-yet-ancient versions of glibc that are broken.
	 * Someday, we will probably want to report a real block
	 * size...  whatever that may mean for a network file system!
	 */
	buf->f_bsize = 1 << CEPH_BLOCK_SHIFT;
	buf->f_frsize = 1 << CEPH_BLOCK_SHIFT;

	/*
	 * By default use root quota for stats; fallback to overall filesystem
	 * usage if using 'noquotadf' mount option or if the root dir doesn't
	 * have max_bytes quota set.
	 */
	if (ceph_test_mount_opt(fsc, NOQUOTADF) ||
	    !ceph_quota_update_statfs(fsc, buf)) {
		buf->f_blocks = le64_to_cpu(st.kb) >> (CEPH_BLOCK_SHIFT-10);
		buf->f_bfree = le64_to_cpu(st.kb_avail) >> (CEPH_BLOCK_SHIFT-10);
		buf->f_bavail = le64_to_cpu(st.kb_avail) >> (CEPH_BLOCK_SHIFT-10);
	}

	buf->f_files = le64_to_cpu(st.num_objects);
	buf->f_ffree = -1;
	buf->f_namelen = NAME_MAX;

	/* Must convert the fsid, for consistent values across arches */
	mutex_lock(&monc->mutex);
	fsid = le64_to_cpu(*(__le64 *)(&monc->monmap->fsid)) ^
	       le64_to_cpu(*((__le64 *)&monc->monmap->fsid + 1));
	mutex_unlock(&monc->mutex);

	buf->f_fsid.val[0] = fsid & 0xffffffff;
	buf->f_fsid.val[1] = fsid >> 32;

	return 0;
}