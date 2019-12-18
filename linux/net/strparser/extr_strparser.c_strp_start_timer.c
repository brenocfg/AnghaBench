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
struct strparser {int /*<<< orphan*/  msg_timer_work; } ;

/* Variables and functions */
 long LONG_MAX ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  strp_wq ; 

__attribute__((used)) static void strp_start_timer(struct strparser *strp, long timeo)
{
	if (timeo && timeo != LONG_MAX)
		mod_delayed_work(strp_wq, &strp->msg_timer_work, timeo);
}