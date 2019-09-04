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
typedef  scalar_t__ time64_t ;
struct watchdog_device {scalar_t__ timeout; } ;
struct TYPE_2__ {scalar_t__ timeout; } ;

/* Variables and functions */
 scalar_t__ ktime_get_seconds () ; 
 TYPE_1__ wdt ; 

__attribute__((used)) static inline time64_t set_timeout(struct watchdog_device *wdd)
{
	wdt.timeout = wdd->timeout;
	return ktime_get_seconds() + wdd->timeout;
}