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
struct ref_action {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*) ; 

__attribute__((used)) static void inline __print_stack_trace(struct btrfs_fs_info *fs_info,
				       struct ref_action *ra)
{
	btrfs_err(fs_info, "  ref-verify: no stacktrace support");
}