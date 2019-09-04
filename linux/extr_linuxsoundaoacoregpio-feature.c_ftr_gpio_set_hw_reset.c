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
struct gpio_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_READ_GPIO ; 
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int SWITCH_GPIO (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hw_reset ; 
 scalar_t__ hw_reset_gpio ; 
 int pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ftr_gpio_set_hw_reset(struct gpio_runtime *rt, int on)
{
	int v;

	if (unlikely(!rt)) return;
	if (hw_reset_gpio < 0)
		return;

	v = pmac_call_feature(PMAC_FTR_READ_GPIO, NULL,
			      hw_reset_gpio, 0);
	v = SWITCH_GPIO(hw_reset, v, on);
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL,
			  hw_reset_gpio, v);
}