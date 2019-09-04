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
struct lp8788 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8788_RTC_UNLOCK ; 
 int /*<<< orphan*/  RTC_LATCH ; 
 int /*<<< orphan*/  RTC_UNLOCK ; 
 int /*<<< orphan*/  lp8788_write_byte (struct lp8788*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp8788_rtc_unlock(struct lp8788 *lp)
{
	lp8788_write_byte(lp, LP8788_RTC_UNLOCK, RTC_UNLOCK);
	lp8788_write_byte(lp, LP8788_RTC_UNLOCK, RTC_LATCH);
}