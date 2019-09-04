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
struct lp8788_buck2_dvs {int vsel; int /*<<< orphan*/ * gpio; } ;
struct lp8788_buck {scalar_t__ dvs; } ;
typedef  enum lp8788_dvs_state { ____Placeholder_lp8788_dvs_state } lp8788_dvs_state ;

/* Variables and functions */
 int DVS_HIGH ; 
 int DVS_LOW ; 
#define  DVS_SEL_V0 131 
#define  DVS_SEL_V1 130 
#define  DVS_SEL_V2 129 
#define  DVS_SEL_V3 128 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lp8788_buck2_set_dvs(struct lp8788_buck *buck)
{
	struct lp8788_buck2_dvs *dvs = (struct lp8788_buck2_dvs *)buck->dvs;
	enum lp8788_dvs_state pin1, pin2;

	if (!dvs)
		return;

	switch (dvs->vsel) {
	case DVS_SEL_V0:
		pin1 = DVS_LOW;
		pin2 = DVS_LOW;
		break;
	case DVS_SEL_V1:
		pin1 = DVS_HIGH;
		pin2 = DVS_LOW;
		break;
	case DVS_SEL_V2:
		pin1 = DVS_LOW;
		pin2 = DVS_HIGH;
		break;
	case DVS_SEL_V3:
		pin1 = DVS_HIGH;
		pin2 = DVS_HIGH;
		break;
	default:
		return;
	}

	if (gpio_is_valid(dvs->gpio[0]))
		gpio_set_value(dvs->gpio[0], pin1);

	if (gpio_is_valid(dvs->gpio[1]))
		gpio_set_value(dvs->gpio[1], pin2);
}