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
struct rk808_rtc {struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_ALARM_M ; 
 int /*<<< orphan*/  RK808_RTC_INT_REG ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk808_rtc_stop_alarm(struct rk808_rtc *rk808_rtc)
{
	struct rk808 *rk808 = rk808_rtc->rk808;
	int ret;

	ret = regmap_update_bits(rk808->regmap, RK808_RTC_INT_REG,
				 BIT_RTC_INTERRUPTS_REG_IT_ALARM_M, 0);

	return ret;
}