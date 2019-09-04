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
struct coda_inode_info {struct inode vfs_inode; int /*<<< orphan*/  c_lock; scalar_t__ c_cached_perm; int /*<<< orphan*/  c_uid; scalar_t__ c_flags; int /*<<< orphan*/  c_fid; } ;
struct CodaFid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  coda_inode_cachep ; 
 struct coda_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *coda_alloc_inode(struct super_block *sb)
{
	struct coda_inode_info *ei;
	ei = kmem_cache_alloc(coda_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;
	memset(&ei->c_fid, 0, sizeof(struct CodaFid));
	ei->c_flags = 0;
	ei->c_uid = GLOBAL_ROOT_UID;
	ei->c_cached_perm = 0;
	spin_lock_init(&ei->c_lock);
	return &ei->vfs_inode;
}