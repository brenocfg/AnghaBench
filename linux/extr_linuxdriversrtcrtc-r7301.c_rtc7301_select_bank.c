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
struct rtc7301_priv {int bank; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  RTC7301_CONTROL ; 
 int RTC7301_CONTROL_BANK_SEL_0 ; 
 int RTC7301_CONTROL_BANK_SEL_1 ; 
 int /*<<< orphan*/  rtc7301_update_bits (struct rtc7301_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtc7301_select_bank(struct rtc7301_priv *priv, u8 bank)
{
	u8 val = 0;

	if (bank == priv->bank)
		return;

	if (bank & BIT(0))
		val |= RTC7301_CONTROL_BANK_SEL_0;
	if (bank & BIT(1))
		val |= RTC7301_CONTROL_BANK_SEL_1;

	rtc7301_update_bits(priv, RTC7301_CONTROL,
			    RTC7301_CONTROL_BANK_SEL_0 |
			    RTC7301_CONTROL_BANK_SEL_1, val);

	priv->bank = bank;
}