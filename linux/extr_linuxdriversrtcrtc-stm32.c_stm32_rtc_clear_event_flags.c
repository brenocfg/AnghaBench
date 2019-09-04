#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stm32_rtc {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear_events ) (struct stm32_rtc*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct stm32_rtc*,unsigned int) ; 

__attribute__((used)) static void stm32_rtc_clear_event_flags(struct stm32_rtc *rtc,
					unsigned int flags)
{
	rtc->data->clear_events(rtc, flags);
}