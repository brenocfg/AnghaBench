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
struct lp872x {int dvs_pin; } ;
typedef  enum lp872x_dvs_state { ____Placeholder_lp872x_dvs_state } lp872x_dvs_state ;
typedef  enum lp872x_dvs_sel { ____Placeholder_lp872x_dvs_sel } lp872x_dvs_sel ;

/* Variables and functions */
 int DVS_HIGH ; 
 int DVS_LOW ; 
 int SEL_V1 ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 

__attribute__((used)) static void lp872x_set_dvs(struct lp872x *lp, enum lp872x_dvs_sel dvs_sel,
			int gpio)
{
	enum lp872x_dvs_state state;

	state = dvs_sel == SEL_V1 ? DVS_HIGH : DVS_LOW;
	gpio_set_value(gpio, state);
	lp->dvs_pin = state;
}