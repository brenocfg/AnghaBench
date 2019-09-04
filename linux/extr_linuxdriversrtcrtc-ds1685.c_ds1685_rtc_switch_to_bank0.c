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
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CTRL_A ; 
 int RTC_CTRL_A_DV0 ; 
 int /*<<< orphan*/  stub1 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ds1685_rtc_switch_to_bank0(struct ds1685_priv *rtc)
{
	rtc->write(rtc, RTC_CTRL_A,
		   (rtc->read(rtc, RTC_CTRL_A) & ~(RTC_CTRL_A_DV0)));
}