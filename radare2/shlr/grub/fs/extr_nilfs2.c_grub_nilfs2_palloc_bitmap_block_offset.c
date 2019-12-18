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
struct grub_nilfs2_data {int dummy; } ;
typedef  scalar_t__ grub_uint32_t ;

/* Variables and functions */
 unsigned long grub_nilfs2_blocks_per_group (struct grub_nilfs2_data*,unsigned long) ; 
 scalar_t__ grub_nilfs2_palloc_desc_block_offset (struct grub_nilfs2_data*,unsigned long,unsigned long) ; 
 unsigned long grub_nilfs2_palloc_groups_per_desc_block (struct grub_nilfs2_data*) ; 

__attribute__((used)) static inline grub_uint32_t
grub_nilfs2_palloc_bitmap_block_offset (struct grub_nilfs2_data *data,
					unsigned long group,
					unsigned long entry_size)
{
  unsigned long desc_offset = group %
    grub_nilfs2_palloc_groups_per_desc_block (data);

  return grub_nilfs2_palloc_desc_block_offset (data, group, entry_size) + 1 +
    desc_offset * grub_nilfs2_blocks_per_group (data, entry_size);
}