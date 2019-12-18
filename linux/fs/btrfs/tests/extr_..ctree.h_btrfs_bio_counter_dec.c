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

/* Variables and functions */
 int /*<<< orphan*/  btrfs_bio_counter_sub (struct btrfs_fs_info*,int) ; 

__attribute__((used)) static inline void btrfs_bio_counter_dec(struct btrfs_fs_info *fs_info)
{
	btrfs_bio_counter_sub(fs_info, 1);
}