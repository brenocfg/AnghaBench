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
struct btrfs_free_space_ctl {scalar_t__ free_extents; scalar_t__ extents_thresh; } ;
struct btrfs_free_space {int bytes; } ;

/* Variables and functions */
 int INODES_PER_BITMAP ; 

__attribute__((used)) static bool use_bitmap(struct btrfs_free_space_ctl *ctl,
		       struct btrfs_free_space *info)
{
	if (ctl->free_extents < ctl->extents_thresh ||
	    info->bytes > INODES_PER_BITMAP / 10)
		return false;

	return true;
}