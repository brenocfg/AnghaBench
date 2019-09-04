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
typedef  int u8 ;
struct as3722_regulators {struct as3722* as3722; } ;
struct as3722 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_LDO3_MODE_MASK ; 
#define  AS3722_LDO3_MODE_NMOS 131 
#define  AS3722_LDO3_MODE_PMOS 130 
#define  AS3722_LDO3_MODE_PMOS_TRACKING 129 
#define  AS3722_LDO3_MODE_SWITCH 128 
 int EINVAL ; 
 TYPE_1__* as3722_reg_lookup ; 
 int as3722_update_bits (struct as3722*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int as3722_ldo3_set_tracking_mode(struct as3722_regulators *as3722_reg,
		int id, u8 mode)
{
	struct as3722 *as3722 = as3722_reg->as3722;

	switch (mode) {
	case AS3722_LDO3_MODE_PMOS:
	case AS3722_LDO3_MODE_PMOS_TRACKING:
	case AS3722_LDO3_MODE_NMOS:
	case AS3722_LDO3_MODE_SWITCH:
		return as3722_update_bits(as3722,
			as3722_reg_lookup[id].vsel_reg,
			AS3722_LDO3_MODE_MASK, mode);

	default:
		return -EINVAL;
	}
}