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
struct btrfs_fs_info {int dummy; } ;
struct __btrfs_workqueue {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */

struct btrfs_fs_info *
btrfs_workqueue_owner(const struct __btrfs_workqueue *wq)
{
	return wq->fs_info;
}