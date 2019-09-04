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
typedef  int /*<<< orphan*/  grub_uint64_t ;
typedef  int grub_uint32_t ;

/* Variables and functions */
 int grub_nilfs2_entries_per_block (struct grub_nilfs2_data*,unsigned long) ; 
 int grub_nilfs2_palloc_bitmap_block_offset (struct grub_nilfs2_data*,unsigned long,unsigned long) ; 
 unsigned long grub_nilfs2_palloc_group (struct grub_nilfs2_data*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline grub_uint32_t
grub_nilfs2_palloc_entry_offset (struct grub_nilfs2_data *data,
				 grub_uint64_t nr, unsigned long entry_size)
{
  unsigned long group;
  grub_uint32_t group_offset;

  group = grub_nilfs2_palloc_group (data, nr, &group_offset);

  return grub_nilfs2_palloc_bitmap_block_offset (data, group,
						 entry_size) + 1 +
    group_offset / grub_nilfs2_entries_per_block (data, entry_size);

}