#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {struct address_space* i_mapping; } ;
struct hugetlbfs_inode_info {int seals; } ;
struct hstate {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;
struct address_space {TYPE_1__ i_mmap; } ;
typedef  int loff_t ;

/* Variables and functions */
 long EPERM ; 
 int F_SEAL_FUTURE_WRITE ; 
 int F_SEAL_WRITE ; 
 struct hugetlbfs_inode_info* HUGETLBFS_I (struct inode*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 struct hstate* hstate_inode (struct inode*) ; 
 int huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_vmdelete_list (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  i_mmap_lock_write (struct address_space*) ; 
 int /*<<< orphan*/  i_mmap_unlock_write (struct address_space*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  remove_inode_hugepages (struct inode*,int,int) ; 
 int round_down (int,int) ; 
 int round_up (int,int) ; 

__attribute__((used)) static long hugetlbfs_punch_hole(struct inode *inode, loff_t offset, loff_t len)
{
	struct hstate *h = hstate_inode(inode);
	loff_t hpage_size = huge_page_size(h);
	loff_t hole_start, hole_end;

	/*
	 * For hole punch round up the beginning offset of the hole and
	 * round down the end.
	 */
	hole_start = round_up(offset, hpage_size);
	hole_end = round_down(offset + len, hpage_size);

	if (hole_end > hole_start) {
		struct address_space *mapping = inode->i_mapping;
		struct hugetlbfs_inode_info *info = HUGETLBFS_I(inode);

		inode_lock(inode);

		/* protected by i_mutex */
		if (info->seals & (F_SEAL_WRITE | F_SEAL_FUTURE_WRITE)) {
			inode_unlock(inode);
			return -EPERM;
		}

		i_mmap_lock_write(mapping);
		if (!RB_EMPTY_ROOT(&mapping->i_mmap.rb_root))
			hugetlb_vmdelete_list(&mapping->i_mmap,
						hole_start >> PAGE_SHIFT,
						hole_end  >> PAGE_SHIFT);
		i_mmap_unlock_write(mapping);
		remove_inode_hugepages(inode, hole_start, hole_end);
		inode_unlock(inode);
	}

	return 0;
}