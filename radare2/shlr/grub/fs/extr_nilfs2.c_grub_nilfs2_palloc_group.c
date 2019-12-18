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
typedef  int /*<<< orphan*/  grub_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_divmod64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grub_nilfs2_palloc_entries_per_group (struct grub_nilfs2_data*) ; 

__attribute__((used)) static inline grub_uint64_t
grub_nilfs2_palloc_group (struct grub_nilfs2_data *data,
			  grub_uint64_t nr, grub_uint32_t * offset)
{
  return grub_divmod64 (nr, grub_nilfs2_palloc_entries_per_group (data),
			offset);
}