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
typedef  int /*<<< orphan*/  time64_t ;
struct timekeeper {int /*<<< orphan*/  ktime_sec; } ;
struct TYPE_2__ {struct timekeeper timekeeper; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timekeeping_suspended ; 
 TYPE_1__ tk_core ; 

time64_t ktime_get_seconds(void)
{
	struct timekeeper *tk = &tk_core.timekeeper;

	WARN_ON(timekeeping_suspended);
	return tk->ktime_sec;
}