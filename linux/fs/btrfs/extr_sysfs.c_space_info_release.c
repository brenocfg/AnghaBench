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
struct kobject {int dummy; } ;
struct btrfs_space_info {int /*<<< orphan*/  total_bytes_pinned; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct btrfs_space_info*) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 struct btrfs_space_info* to_space_info (struct kobject*) ; 

__attribute__((used)) static void space_info_release(struct kobject *kobj)
{
	struct btrfs_space_info *sinfo = to_space_info(kobj);
	percpu_counter_destroy(&sinfo->total_bytes_pinned);
	kfree(sinfo);
}