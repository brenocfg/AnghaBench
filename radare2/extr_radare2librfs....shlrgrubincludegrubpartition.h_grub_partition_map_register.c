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
typedef  int /*<<< orphan*/  grub_partition_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_AS_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRUB_AS_LIST_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GRUB_MODATTR (char*,char*) ; 
 int /*<<< orphan*/  grub_list_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_partition_map_list ; 

__attribute__((used)) static inline void
grub_partition_map_register (grub_partition_map_t partmap)
{
  grub_list_push (GRUB_AS_LIST_P (&grub_partition_map_list),
		  GRUB_AS_LIST (partmap));
  GRUB_MODATTR ("partmap", "");
}