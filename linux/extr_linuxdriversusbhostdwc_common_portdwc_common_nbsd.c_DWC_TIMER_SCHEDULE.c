#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cb; int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ dwc_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

void DWC_TIMER_SCHEDULE(dwc_timer_t *timer, uint32_t time)
{
	struct timeval tv;

	tv.tv_sec = time / 1000;
	tv.tv_usec = (time - tv.tv_sec * 1000) * 1000;
	callout_reset(&timer->t, tvtohz(&tv), timer->cb, timer->data);
}