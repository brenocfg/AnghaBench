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
struct buffer_head {scalar_t__ b_private; } ;
struct btrfs_device {int /*<<< orphan*/  name; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_STAT_WRITE_ERRS ; 
 int /*<<< orphan*/  btrfs_dev_stat_inc_and_print (struct btrfs_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn_rl_in_rcu (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  rcu_str_deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void btrfs_end_buffer_write_sync(struct buffer_head *bh, int uptodate)
{
	if (uptodate) {
		set_buffer_uptodate(bh);
	} else {
		struct btrfs_device *device = (struct btrfs_device *)
			bh->b_private;

		btrfs_warn_rl_in_rcu(device->fs_info,
				"lost page write due to IO error on %s",
					  rcu_str_deref(device->name));
		/* note, we don't set_buffer_write_io_error because we have
		 * our own ways of dealing with the IO errors
		 */
		clear_buffer_uptodate(bh);
		btrfs_dev_stat_inc_and_print(device, BTRFS_DEV_STAT_WRITE_ERRS);
	}
	unlock_buffer(bh);
	put_bh(bh);
}