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
 unsigned long GET_BITS (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPX_BOUNDS_TABLE_BOTTOM_BIT ; 
 int /*<<< orphan*/  MPX_BOUNDS_TABLE_TOP_BIT ; 

__attribute__((used)) static inline unsigned long __vaddr_bounds_table_index(void *vaddr)
{
	return GET_BITS((unsigned long)vaddr, MPX_BOUNDS_TABLE_BOTTOM_BIT,
					      MPX_BOUNDS_TABLE_TOP_BIT);
}