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
typedef  int ulong ;
struct gasket_page_table {int dummy; } ;

/* Variables and functions */
 int GASKET_EXTENDED_LVL0_SHIFT ; 
 int GASKET_EXTENDED_LVL0_WIDTH ; 

__attribute__((used)) static ulong gasket_extended_lvl0_page_idx(struct gasket_page_table *pg_tbl,
					   ulong dev_addr)
{
	return (dev_addr >> GASKET_EXTENDED_LVL0_SHIFT) &
	       ((1 << GASKET_EXTENDED_LVL0_WIDTH) - 1);
}