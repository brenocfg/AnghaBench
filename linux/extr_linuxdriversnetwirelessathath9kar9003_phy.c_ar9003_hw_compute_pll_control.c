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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RTC_9300_PLL_CLKSEL ; 
 int /*<<< orphan*/  AR_RTC_9300_PLL_DIV ; 
 int /*<<< orphan*/  AR_RTC_9300_PLL_REFDIV ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 int /*<<< orphan*/  SM (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ar9003_hw_compute_pll_control(struct ath_hw *ah,
					 struct ath9k_channel *chan)
{
	u32 pll;

	pll = SM(0x5, AR_RTC_9300_PLL_REFDIV);

	if (chan && IS_CHAN_HALF_RATE(chan))
		pll |= SM(0x1, AR_RTC_9300_PLL_CLKSEL);
	else if (chan && IS_CHAN_QUARTER_RATE(chan))
		pll |= SM(0x2, AR_RTC_9300_PLL_CLKSEL);

	pll |= SM(0x2c, AR_RTC_9300_PLL_DIV);

	return pll;
}