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
struct auto_pin_cfg_item {scalar_t__ type; scalar_t__ has_boost_on_pin; } ;

/* Variables and functions */

__attribute__((used)) static int compare_input_type(const void *ap, const void *bp)
{
	const struct auto_pin_cfg_item *a = ap;
	const struct auto_pin_cfg_item *b = bp;
	if (a->type != b->type)
		return (int)(a->type - b->type);

	/* In case one has boost and the other one has not,
	   pick the one with boost first. */
	return (int)(b->has_boost_on_pin - a->has_boost_on_pin);
}