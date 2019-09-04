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
typedef  int u64 ;

/* Variables and functions */

u64 vgic_sanitise_field(u64 reg, u64 field_mask, int field_shift,
			u64 (*sanitise_fn)(u64))
{
	u64 field = (reg & field_mask) >> field_shift;

	field = sanitise_fn(field) << field_shift;
	return (reg & ~field_mask) | field;
}