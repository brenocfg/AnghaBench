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

/* Variables and functions */
 int REISERFS_DATA_LOG ; 
 int REISERFS_DATA_ORDERED ; 
 int REISERFS_DATA_WRITEBACK ; 
 int /*<<< orphan*/  reiserfs_data_log (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_data_ordered (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_data_writeback (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_info (struct super_block*,char*) ; 
 int /*<<< orphan*/  switch_data_mode (struct super_block*,int) ; 

__attribute__((used)) static void handle_data_mode(struct super_block *s, unsigned long mount_options)
{
	if (mount_options & (1 << REISERFS_DATA_LOG)) {
		if (!reiserfs_data_log(s)) {
			switch_data_mode(s, REISERFS_DATA_LOG);
			reiserfs_info(s, "switching to journaled data mode\n");
		}
	} else if (mount_options & (1 << REISERFS_DATA_ORDERED)) {
		if (!reiserfs_data_ordered(s)) {
			switch_data_mode(s, REISERFS_DATA_ORDERED);
			reiserfs_info(s, "switching to ordered data mode\n");
		}
	} else if (mount_options & (1 << REISERFS_DATA_WRITEBACK)) {
		if (!reiserfs_data_writeback(s)) {
			switch_data_mode(s, REISERFS_DATA_WRITEBACK);
			reiserfs_info(s, "switching to writeback data mode\n");
		}
	}
}