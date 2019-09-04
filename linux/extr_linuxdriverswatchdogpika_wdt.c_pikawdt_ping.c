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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  open; int /*<<< orphan*/  next_heartbeat; } ;

/* Variables and functions */
 scalar_t__ WDT_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nowayout ; 
 TYPE_1__ pikawdt_private ; 
 int /*<<< orphan*/  pikawdt_reset () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pikawdt_ping(struct timer_list *unused)
{
	if (time_before(jiffies, pikawdt_private.next_heartbeat) ||
			(!nowayout && !pikawdt_private.open)) {
		pikawdt_reset();
		mod_timer(&pikawdt_private.timer, jiffies + WDT_TIMEOUT);
	} else
		pr_crit("I will reset your machine !\n");
}