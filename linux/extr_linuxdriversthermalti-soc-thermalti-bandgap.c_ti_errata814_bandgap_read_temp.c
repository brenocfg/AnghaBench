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
typedef  scalar_t__ u32 ;
struct ti_bandgap {int dummy; } ;

/* Variables and functions */
 scalar_t__ ti_bandgap_readl (struct ti_bandgap*,scalar_t__) ; 

__attribute__((used)) static u32 ti_errata814_bandgap_read_temp(struct ti_bandgap *bgp,  u32 reg)
{
	u32 val1, val2;

	val1 = ti_bandgap_readl(bgp, reg);
	val2 = ti_bandgap_readl(bgp, reg);

	/* If both times we read the same value then that is right */
	if (val1 == val2)
		return val1;

	/* if val1 and val2 are different read it third time */
	return ti_bandgap_readl(bgp, reg);
}