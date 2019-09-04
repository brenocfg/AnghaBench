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
struct mpx_bt_entry {int dummy; } ;
struct mpx_bounds_table {struct mpx_bt_entry* entries; } ;
struct mpx_bounds_dir {int dummy; } ;
struct mpx_bd_entry {int dummy; } ;

/* Variables and functions */
 struct mpx_bounds_table* __bd_entry_to_bounds_table (struct mpx_bd_entry*) ; 
 unsigned long __vaddr_bounds_table_index (void*) ; 
 struct mpx_bd_entry* mpx_vaddr_to_bd_entry (void*,struct mpx_bounds_dir*) ; 

__attribute__((used)) static inline struct mpx_bt_entry *
mpx_vaddr_to_bt_entry(void *vaddr, struct mpx_bounds_dir *bounds_dir)
{
	struct mpx_bd_entry *bde = mpx_vaddr_to_bd_entry(vaddr, bounds_dir);
	struct mpx_bounds_table *bt = __bd_entry_to_bounds_table(bde);
	unsigned long index = __vaddr_bounds_table_index(vaddr);
	return &bt->entries[index];
}