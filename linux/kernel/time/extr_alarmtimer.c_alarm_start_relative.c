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
struct alarm_base {int /*<<< orphan*/  (* gettime ) () ;} ;
struct alarm {size_t type; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct alarm_base* alarm_bases ; 
 int /*<<< orphan*/  alarm_start (struct alarm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void alarm_start_relative(struct alarm *alarm, ktime_t start)
{
	struct alarm_base *base = &alarm_bases[alarm->type];

	start = ktime_add_safe(start, base->gettime());
	alarm_start(alarm, start);
}