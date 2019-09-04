#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int uint ;
struct TYPE_2__ {int total_entries; } ;
struct gasket_page_table {int extended_flag; TYPE_1__ config; } ;

/* Variables and functions */
 int GASKET_EXTENDED_LVL0_SHIFT ; 
 int GASKET_EXTENDED_LVL1_SHIFT ; 
 int GASKET_PAGES_PER_SUBTABLE ; 
 int GASKET_SIMPLE_PAGE_SHIFT ; 

__attribute__((used)) static ulong gasket_components_to_dev_address(struct gasket_page_table *pg_tbl,
					      int is_simple, uint page_index,
					      uint offset)
{
	ulong lvl0_index, lvl1_index;

	if (is_simple) {
		/* Return simple addresses directly. */
		lvl0_index = page_index & (pg_tbl->config.total_entries - 1);
		return (lvl0_index << GASKET_SIMPLE_PAGE_SHIFT) | offset;
	}

	/*
	 * This could be compressed into fewer statements, but
	 * A) the compiler should optimize it
	 * B) this is not slow
	 * C) this is an uncommon operation
	 * D) this is actually readable this way.
	 */
	lvl0_index = page_index / GASKET_PAGES_PER_SUBTABLE;
	lvl1_index = page_index & (GASKET_PAGES_PER_SUBTABLE - 1);
	return (pg_tbl)->extended_flag |
	       (lvl0_index << GASKET_EXTENDED_LVL0_SHIFT) |
	       (lvl1_index << GASKET_EXTENDED_LVL1_SHIFT) | offset;
}