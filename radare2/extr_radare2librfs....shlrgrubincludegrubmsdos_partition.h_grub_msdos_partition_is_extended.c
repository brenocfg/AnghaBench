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

/* Variables and functions */
 int GRUB_PC_PARTITION_TYPE_EXTENDED ; 
 int GRUB_PC_PARTITION_TYPE_LINUX_EXTENDED ; 
 int GRUB_PC_PARTITION_TYPE_WIN95_EXTENDED ; 

__attribute__((used)) static inline int
grub_msdos_partition_is_extended (int type)
{
  return (type == GRUB_PC_PARTITION_TYPE_EXTENDED
	  || type == GRUB_PC_PARTITION_TYPE_WIN95_EXTENDED
	  || type == GRUB_PC_PARTITION_TYPE_LINUX_EXTENDED);
}