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
struct mpx_bounds_table {int dummy; } ;
struct mpx_bd_entry {scalar_t__ contents; } ;

/* Variables and functions */
 unsigned long MPX_BOUNDS_TABLE_ENTRY_VALID_BIT ; 
 int /*<<< orphan*/  assert (unsigned long) ; 

__attribute__((used)) static inline struct mpx_bounds_table *
__bd_entry_to_bounds_table(struct mpx_bd_entry *bounds_dir_entry)
{
	unsigned long __bd_entry = (unsigned long)bounds_dir_entry->contents;
	assert(__bd_entry & MPX_BOUNDS_TABLE_ENTRY_VALID_BIT);
	__bd_entry &= ~MPX_BOUNDS_TABLE_ENTRY_VALID_BIT;
	return (struct mpx_bounds_table *)__bd_entry;
}