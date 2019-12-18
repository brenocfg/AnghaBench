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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct hugetlbfs_sb_info {int dummy; } ;
struct hugetlbfs_inode_info {struct inode vfs_inode; int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hugetlbfs_sb_info* HUGETLBFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  hugetlbfs_dec_free_inodes (struct hugetlbfs_sb_info*) ; 
 int /*<<< orphan*/  hugetlbfs_inc_free_inodes (struct hugetlbfs_sb_info*) ; 
 int /*<<< orphan*/  hugetlbfs_inode_cachep ; 
 struct hugetlbfs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_shared_policy_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct inode *hugetlbfs_alloc_inode(struct super_block *sb)
{
	struct hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(sb);
	struct hugetlbfs_inode_info *p;

	if (unlikely(!hugetlbfs_dec_free_inodes(sbinfo)))
		return NULL;
	p = kmem_cache_alloc(hugetlbfs_inode_cachep, GFP_KERNEL);
	if (unlikely(!p)) {
		hugetlbfs_inc_free_inodes(sbinfo);
		return NULL;
	}

	/*
	 * Any time after allocation, hugetlbfs_destroy_inode can be called
	 * for the inode.  mpol_free_shared_policy is unconditionally called
	 * as part of hugetlbfs_destroy_inode.  So, initialize policy here
	 * in case of a quick call to destroy.
	 *
	 * Note that the policy is initialized even if we are creating a
	 * private inode.  This simplifies hugetlbfs_destroy_inode.
	 */
	mpol_shared_policy_init(&p->policy, NULL);

	return &p->vfs_inode;
}