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
struct orangefs_inode_s {unsigned long bitlock; scalar_t__ mapping_time; } ;
struct inode {int /*<<< orphan*/  i_lock; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 struct orangefs_inode_s* ORANGEFS_I (struct inode*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int filemap_write_and_wait (struct address_space*) ; 
 int invalidate_inode_pages2 (struct address_space*) ; 
 scalar_t__ jiffies ; 
 int orangefs_cache_timeout_msecs ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_on_bit (unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (unsigned long*,int) ; 

int orangefs_revalidate_mapping(struct inode *inode)
{
	struct orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	struct address_space *mapping = inode->i_mapping;
	unsigned long *bitlock = &orangefs_inode->bitlock;
	int ret;

	while (1) {
		ret = wait_on_bit(bitlock, 1, TASK_KILLABLE);
		if (ret)
			return ret;
		spin_lock(&inode->i_lock);
		if (test_bit(1, bitlock)) {
			spin_unlock(&inode->i_lock);
			continue;
		}
		if (!time_before(jiffies, orangefs_inode->mapping_time))
			break;
		spin_unlock(&inode->i_lock);
		return 0;
	}

	set_bit(1, bitlock);
	smp_wmb();
	spin_unlock(&inode->i_lock);

	unmap_mapping_range(mapping, 0, 0, 0);
	ret = filemap_write_and_wait(mapping);
	if (!ret)
		ret = invalidate_inode_pages2(mapping);

	orangefs_inode->mapping_time = jiffies +
	    orangefs_cache_timeout_msecs*HZ/1000;

	clear_bit(1, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, 1);

	return ret;
}