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
struct TYPE_4__ {int hash; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_2__ d_name; } ;
struct TYPE_3__ {int dl_dir_hash; } ;
struct ceph_inode_info {TYPE_1__ i_dir_layout; } ;

/* Variables and functions */
#define  CEPH_STR_HASH_LINUX 128 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 unsigned int ceph_str_hash (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned ceph_dentry_hash(struct inode *dir, struct dentry *dn)
{
	struct ceph_inode_info *dci = ceph_inode(dir);
	unsigned hash;

	switch (dci->i_dir_layout.dl_dir_hash) {
	case 0:	/* for backward compat */
	case CEPH_STR_HASH_LINUX:
		return dn->d_name.hash;

	default:
		spin_lock(&dn->d_lock);
		hash = ceph_str_hash(dci->i_dir_layout.dl_dir_hash,
				     dn->d_name.name, dn->d_name.len);
		spin_unlock(&dn->d_lock);
		return hash;
	}
}