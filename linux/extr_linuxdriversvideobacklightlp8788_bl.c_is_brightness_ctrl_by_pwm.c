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
typedef  enum lp8788_bl_ctrl_mode { ____Placeholder_lp8788_bl_ctrl_mode } lp8788_bl_ctrl_mode ;

/* Variables and functions */
 int LP8788_BL_COMB_PWM_BASED ; 

__attribute__((used)) static inline bool is_brightness_ctrl_by_pwm(enum lp8788_bl_ctrl_mode mode)
{
	return mode == LP8788_BL_COMB_PWM_BASED;
}