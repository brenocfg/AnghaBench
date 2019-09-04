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
typedef  int u8 ;
struct max8998_rtc_info {scalar_t__ lp3974_bug_workaround; int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8998_ALARM0_CONF ; 
 int max8998_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int max8998_rtc_start_alarm(struct max8998_rtc_info *info)
{
	int ret;
	u8 alarm0_conf = 0x77;

	/* LP3974 with delay bug chips has rtc alarm bugs with "MONTH" field */
	if (info->lp3974_bug_workaround)
		alarm0_conf = 0x57;

	ret = max8998_write_reg(info->rtc, MAX8998_ALARM0_CONF, alarm0_conf);

	if (info->lp3974_bug_workaround)
		msleep(2000);

	return ret;
}