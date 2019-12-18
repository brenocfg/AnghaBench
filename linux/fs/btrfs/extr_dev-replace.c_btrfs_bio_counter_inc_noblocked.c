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
struct TYPE_2__ {int /*<<< orphan*/  bio_counter; } ;
struct btrfs_fs_info {TYPE_1__ dev_replace; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 

void btrfs_bio_counter_inc_noblocked(struct btrfs_fs_info *fs_info)
{
	percpu_counter_inc(&fs_info->dev_replace.bio_counter);
}