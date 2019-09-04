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
struct grub_nilfs2_palloc_group_desc {int dummy; } ;
struct grub_nilfs2_data {int dummy; } ;
typedef  int grub_uint32_t ;

/* Variables and functions */
 int NILFS2_BLOCK_SIZE (struct grub_nilfs2_data*) ; 

__attribute__((used)) static inline grub_uint32_t
grub_nilfs2_palloc_groups_per_desc_block (struct grub_nilfs2_data *data)
{
  return NILFS2_BLOCK_SIZE (data) /
    sizeof (struct grub_nilfs2_palloc_group_desc);
}