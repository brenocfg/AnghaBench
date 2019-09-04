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

/* Variables and functions */
 int EINVAL ; 
 int GEODEWDT_HZ ; 
 int GEODEWDT_MAX_SECONDS ; 
 int /*<<< orphan*/  MFGPT_REG_CMP2 ; 
 int /*<<< orphan*/  MFGPT_REG_COUNTER ; 
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int MFGPT_SETUP_CNTEN ; 
 int /*<<< orphan*/  cs5535_mfgpt_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int timeout ; 
 int /*<<< orphan*/  wdt_timer ; 

__attribute__((used)) static int geodewdt_set_heartbeat(int val)
{
	if (val < 1 || val > GEODEWDT_MAX_SECONDS)
		return -EINVAL;

	cs5535_mfgpt_write(wdt_timer, MFGPT_REG_SETUP, 0);
	cs5535_mfgpt_write(wdt_timer, MFGPT_REG_CMP2, val * GEODEWDT_HZ);
	cs5535_mfgpt_write(wdt_timer, MFGPT_REG_COUNTER, 0);
	cs5535_mfgpt_write(wdt_timer, MFGPT_REG_SETUP, MFGPT_SETUP_CNTEN);

	timeout = val;
	return 0;
}