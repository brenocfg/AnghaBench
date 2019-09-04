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
struct timer_list {int dummy; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags2; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_TIMER_TICK ; 
 struct esas2r_adapter* a ; 
 int /*<<< orphan*/  esas2r_kickoff_timer (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_schedule_tasklet (struct esas2r_adapter*) ; 
 struct esas2r_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void esas2r_timer_callback(struct timer_list *t)
{
	struct esas2r_adapter *a = from_timer(a, t, timer);

	set_bit(AF2_TIMER_TICK, &a->flags2);

	esas2r_schedule_tasklet(a);

	esas2r_kickoff_timer(a);
}