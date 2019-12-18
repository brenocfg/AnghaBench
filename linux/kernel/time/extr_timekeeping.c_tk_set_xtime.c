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
typedef  int u64 ;
struct timespec64 {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int xtime_nsec; int shift; } ;
struct timekeeper {TYPE_1__ tkr_mono; int /*<<< orphan*/  xtime_sec; } ;

/* Variables and functions */

__attribute__((used)) static void tk_set_xtime(struct timekeeper *tk, const struct timespec64 *ts)
{
	tk->xtime_sec = ts->tv_sec;
	tk->tkr_mono.xtime_nsec = (u64)ts->tv_nsec << tk->tkr_mono.shift;
}