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
struct TYPE_2__ {int /*<<< orphan*/  first_data_block; } ;
struct grub_ext2_data {TYPE_1__ sblock; int /*<<< orphan*/  disk; } ;
struct grub_ext2_block_group {int dummy; } ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int LOG2_EXT2_BLOCK_SIZE (struct grub_ext2_data*) ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int,int,struct grub_ext2_block_group*) ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static grub_err_t
grub_ext2_blockgroup (struct grub_ext2_data *data, int group,
		      struct grub_ext2_block_group *blkgrp)
{
  return grub_disk_read (data->disk,
                         ((grub_le_to_cpu32 (data->sblock.first_data_block) + 1)
                          << LOG2_EXT2_BLOCK_SIZE (data)),
			 group * sizeof (struct grub_ext2_block_group),
			 sizeof (struct grub_ext2_block_group), blkgrp);
}