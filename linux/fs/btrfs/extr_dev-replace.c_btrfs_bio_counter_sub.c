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
struct TYPE_2__ {int /*<<< orphan*/  replace_wait; int /*<<< orphan*/  bio_counter; } ;
struct btrfs_fs_info {TYPE_1__ dev_replace; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  cond_wake_up_nomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btrfs_bio_counter_sub(struct btrfs_fs_info *fs_info, s64 amount)
{
	percpu_counter_sub(&fs_info->dev_replace.bio_counter, amount);
	cond_wake_up_nomb(&fs_info->dev_replace.replace_wait);
}