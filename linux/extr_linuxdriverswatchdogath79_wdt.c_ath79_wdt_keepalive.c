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
 int /*<<< orphan*/  WDOG_REG_TIMER ; 
 int /*<<< orphan*/  ath79_wdt_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_wdt_wr (int /*<<< orphan*/ ,int) ; 
 int timeout ; 
 int wdt_freq ; 

__attribute__((used)) static inline void ath79_wdt_keepalive(void)
{
	ath79_wdt_wr(WDOG_REG_TIMER, wdt_freq * timeout);
	/* flush write */
	ath79_wdt_rr(WDOG_REG_TIMER);
}