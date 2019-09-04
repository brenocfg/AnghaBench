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
struct lp8788_buck1_dvs {scalar_t__ vsel; int /*<<< orphan*/  gpio; } ;
struct lp8788_buck {scalar_t__ dvs; } ;
typedef  enum lp8788_dvs_state { ____Placeholder_lp8788_dvs_state } lp8788_dvs_state ;

/* Variables and functions */
 int DVS_HIGH ; 
 int DVS_LOW ; 
 scalar_t__ DVS_SEL_V0 ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lp8788_buck1_set_dvs(struct lp8788_buck *buck)
{
	struct lp8788_buck1_dvs *dvs = (struct lp8788_buck1_dvs *)buck->dvs;
	enum lp8788_dvs_state pinstate;

	if (!dvs)
		return;

	pinstate = dvs->vsel == DVS_SEL_V0 ? DVS_LOW : DVS_HIGH;
	if (gpio_is_valid(dvs->gpio))
		gpio_set_value(dvs->gpio, pinstate);
}