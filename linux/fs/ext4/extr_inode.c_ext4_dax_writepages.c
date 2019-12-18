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
struct writeback_control {long nr_to_write; } ;
struct inode {TYPE_1__* i_sb; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_journal_flag_rwsem; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int EIO ; 
 struct ext4_sb_info* EXT4_SB (TYPE_1__*) ; 
 int dax_writeback_mapping_range (struct address_space*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (struct ext4_sb_info*) ; 
 int /*<<< orphan*/  percpu_down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ext4_writepages (struct inode*,struct writeback_control*) ; 
 int /*<<< orphan*/  trace_ext4_writepages_result (struct inode*,struct writeback_control*,int,long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_dax_writepages(struct address_space *mapping,
			       struct writeback_control *wbc)
{
	int ret;
	long nr_to_write = wbc->nr_to_write;
	struct inode *inode = mapping->host;
	struct ext4_sb_info *sbi = EXT4_SB(mapping->host->i_sb);

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	percpu_down_read(&sbi->s_journal_flag_rwsem);
	trace_ext4_writepages(inode, wbc);

	ret = dax_writeback_mapping_range(mapping, inode->i_sb->s_bdev, wbc);
	trace_ext4_writepages_result(inode, wbc, ret,
				     nr_to_write - wbc->nr_to_write);
	percpu_up_read(&sbi->s_journal_flag_rwsem);
	return ret;
}