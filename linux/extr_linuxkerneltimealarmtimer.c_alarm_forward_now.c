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
typedef  int /*<<< orphan*/  u64 ;
struct alarm_base {int /*<<< orphan*/  (* gettime ) () ;} ;
struct alarm {size_t type; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct alarm_base* alarm_bases ; 
 int /*<<< orphan*/  alarm_forward (struct alarm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

u64 alarm_forward_now(struct alarm *alarm, ktime_t interval)
{
	struct alarm_base *base = &alarm_bases[alarm->type];

	return alarm_forward(alarm, base->gettime(), interval);
}