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
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {int /*<<< orphan*/  dedupe_in_progress; TYPE_1__ root_key; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_warn_rl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dedupe_in_progress_warn(const struct btrfs_root *root)
{
	btrfs_warn_rl(root->fs_info,
"cannot use root %llu for send while deduplications on it are in progress (%d in progress)",
		      root->root_key.objectid, root->dedupe_in_progress);
}