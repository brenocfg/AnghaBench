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

/* Variables and functions */
 int LOG2_BLOCK_SIZE (struct grub_nilfs2_data*) ; 

__attribute__((used)) static inline unsigned long
grub_nilfs2_palloc_entries_per_group (struct grub_nilfs2_data *data)
{
  return 1UL << (LOG2_BLOCK_SIZE (data) + 3);
}