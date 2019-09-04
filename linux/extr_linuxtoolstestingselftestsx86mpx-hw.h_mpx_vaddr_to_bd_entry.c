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
struct mpx_bounds_dir {struct mpx_bd_entry* entries; } ;
struct mpx_bd_entry {int dummy; } ;

/* Variables and functions */
 unsigned long __vaddr_bounds_directory_index (void*) ; 

__attribute__((used)) static inline struct mpx_bd_entry *mpx_vaddr_to_bd_entry(void *vaddr,
		struct mpx_bounds_dir *bounds_dir)
{
	unsigned long index = __vaddr_bounds_directory_index(vaddr);
	return &bounds_dir->entries[index];
}