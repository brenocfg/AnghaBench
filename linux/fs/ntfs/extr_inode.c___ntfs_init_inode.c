#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * base_ntfs_ino; } ;
struct TYPE_7__ {scalar_t__ vcn_size_bits; scalar_t__ block_size_bits; scalar_t__ collation_rule; scalar_t__ vcn_size; scalar_t__ block_size; } ;
struct TYPE_8__ {TYPE_1__ index; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_3__ ext; scalar_t__ nr_extents; int /*<<< orphan*/  extent_lock; TYPE_2__ itype; TYPE_5__ attr_list_rl; int /*<<< orphan*/ * attr_list; scalar_t__ attr_list_size; scalar_t__ page_ofs; int /*<<< orphan*/ * page; int /*<<< orphan*/  mrec_lock; TYPE_5__ runlist; int /*<<< orphan*/  vol; int /*<<< orphan*/  count; scalar_t__ seq_no; scalar_t__ allocated_size; scalar_t__ initialized_size; int /*<<< orphan*/  size_lock; } ;
typedef  TYPE_4__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  NTFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  attr_list_rl_lock_class ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/  ntfs_init_runlist (TYPE_5__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

void __ntfs_init_inode(struct super_block *sb, ntfs_inode *ni)
{
	ntfs_debug("Entering.");
	rwlock_init(&ni->size_lock);
	ni->initialized_size = ni->allocated_size = 0;
	ni->seq_no = 0;
	atomic_set(&ni->count, 1);
	ni->vol = NTFS_SB(sb);
	ntfs_init_runlist(&ni->runlist);
	mutex_init(&ni->mrec_lock);
	ni->page = NULL;
	ni->page_ofs = 0;
	ni->attr_list_size = 0;
	ni->attr_list = NULL;
	ntfs_init_runlist(&ni->attr_list_rl);
	lockdep_set_class(&ni->attr_list_rl.lock,
				&attr_list_rl_lock_class);
	ni->itype.index.block_size = 0;
	ni->itype.index.vcn_size = 0;
	ni->itype.index.collation_rule = 0;
	ni->itype.index.block_size_bits = 0;
	ni->itype.index.vcn_size_bits = 0;
	mutex_init(&ni->extent_lock);
	ni->nr_extents = 0;
	ni->ext.base_ntfs_ino = NULL;
}