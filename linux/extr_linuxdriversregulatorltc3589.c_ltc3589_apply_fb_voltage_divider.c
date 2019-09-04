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
struct regulator_desc {void* fixed_uV; void* uV_step; void* min_uV; } ;
struct ltc3589_regulator {int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; struct regulator_desc desc; } ;

/* Variables and functions */
 void* ltc3589_scale (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltc3589_apply_fb_voltage_divider(struct ltc3589_regulator *rdesc)
{
	struct regulator_desc *desc = &rdesc->desc;

	if (!rdesc->r1 || !rdesc->r2)
		return;

	desc->min_uV = ltc3589_scale(desc->min_uV, rdesc->r1, rdesc->r2);
	desc->uV_step = ltc3589_scale(desc->uV_step, rdesc->r1, rdesc->r2);
	desc->fixed_uV = ltc3589_scale(desc->fixed_uV, rdesc->r1, rdesc->r2);
}