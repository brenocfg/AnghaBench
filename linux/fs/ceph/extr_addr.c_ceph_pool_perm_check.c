#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ceph_string {int dummy; } ;
struct TYPE_4__ {scalar_t__ pool_id; int /*<<< orphan*/  pool_ns; } ;
struct TYPE_3__ {scalar_t__ snap; } ;
struct ceph_inode_info {int i_ceph_flags; int /*<<< orphan*/  i_ceph_lock; TYPE_2__ i_layout; TYPE_1__ i_vino; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int CEPH_CAP_FILE_RD ; 
 int CEPH_CAP_FILE_WR ; 
 int CEPH_I_POOL_PERM ; 
 int CEPH_I_POOL_RD ; 
 int CEPH_I_POOL_WR ; 
 scalar_t__ CEPH_NOSNAP ; 
 int EPERM ; 
 int /*<<< orphan*/  NOPOOLPERM ; 
 int POOL_READ ; 
 int POOL_WRITE ; 
 int __ceph_pool_perm_get (struct ceph_inode_info*,scalar_t__,struct ceph_string*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_string (struct ceph_string*) ; 
 scalar_t__ ceph_test_mount_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ceph_string* ceph_try_get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,scalar_t__) ; 
 struct ceph_string* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ceph_pool_perm_check(struct inode *inode, int need)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_string *pool_ns;
	s64 pool;
	int ret, flags;

	if (ci->i_vino.snap != CEPH_NOSNAP) {
		/*
		 * Pool permission check needs to write to the first object.
		 * But for snapshot, head of the first object may have alread
		 * been deleted. Skip check to avoid creating orphan object.
		 */
		return 0;
	}

	if (ceph_test_mount_opt(ceph_inode_to_client(inode),
				NOPOOLPERM))
		return 0;

	spin_lock(&ci->i_ceph_lock);
	flags = ci->i_ceph_flags;
	pool = ci->i_layout.pool_id;
	spin_unlock(&ci->i_ceph_lock);
check:
	if (flags & CEPH_I_POOL_PERM) {
		if ((need & CEPH_CAP_FILE_RD) && !(flags & CEPH_I_POOL_RD)) {
			dout("ceph_pool_perm_check pool %lld no read perm\n",
			     pool);
			return -EPERM;
		}
		if ((need & CEPH_CAP_FILE_WR) && !(flags & CEPH_I_POOL_WR)) {
			dout("ceph_pool_perm_check pool %lld no write perm\n",
			     pool);
			return -EPERM;
		}
		return 0;
	}

	pool_ns = ceph_try_get_string(ci->i_layout.pool_ns);
	ret = __ceph_pool_perm_get(ci, pool, pool_ns);
	ceph_put_string(pool_ns);
	if (ret < 0)
		return ret;

	flags = CEPH_I_POOL_PERM;
	if (ret & POOL_READ)
		flags |= CEPH_I_POOL_RD;
	if (ret & POOL_WRITE)
		flags |= CEPH_I_POOL_WR;

	spin_lock(&ci->i_ceph_lock);
	if (pool == ci->i_layout.pool_id &&
	    pool_ns == rcu_dereference_raw(ci->i_layout.pool_ns)) {
		ci->i_ceph_flags |= flags;
        } else {
		pool = ci->i_layout.pool_id;
		flags = ci->i_ceph_flags;
	}
	spin_unlock(&ci->i_ceph_lock);
	goto check;
}