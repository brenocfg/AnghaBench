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
struct kobj_attribute {int dummy; } ;
struct btrfs_space_info {int /*<<< orphan*/  total_bytes_pinned; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct btrfs_space_info* to_space_info (struct kobject*) ; 

__attribute__((used)) static ssize_t btrfs_space_info_show_total_bytes_pinned(struct kobject *kobj,
						       struct kobj_attribute *a,
						       char *buf)
{
	struct btrfs_space_info *sinfo = to_space_info(kobj);
	s64 val = percpu_counter_sum(&sinfo->total_bytes_pinned);
	return snprintf(buf, PAGE_SIZE, "%lld\n", val);
}