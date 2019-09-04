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
struct rtc_device {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static bool is_rtc_hctosys(struct rtc_device *rtc)
{
	return (rtc->id == 0);
}