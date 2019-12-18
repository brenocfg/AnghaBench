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
struct super_block {TYPE_3__* s_root; } ;
struct inode {int dummy; } ;
struct ceph_mds_client {int /*<<< orphan*/  quotarealms_count; TYPE_1__* fsc; } ;
struct TYPE_8__ {struct ceph_mds_client* mdsc; } ;
struct TYPE_7__ {TYPE_2__* d_inode; } ;
struct TYPE_6__ {scalar_t__ i_ino; } ;
struct TYPE_5__ {struct super_block* sb; } ;

/* Variables and functions */
 scalar_t__ CEPH_INO_ROOT ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 TYPE_4__* ceph_inode_to_client (struct inode*) ; 

__attribute__((used)) static inline bool ceph_has_realms_with_quotas(struct inode *inode)
{
	struct ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	struct super_block *sb = mdsc->fsc->sb;

	if (atomic64_read(&mdsc->quotarealms_count) > 0)
		return true;
	/* if root is the real CephFS root, we don't have quota realms */
	if (sb->s_root->d_inode &&
	    (sb->s_root->d_inode->i_ino == CEPH_INO_ROOT))
		return false;
	/* otherwise, we can't know for sure */
	return true;
}