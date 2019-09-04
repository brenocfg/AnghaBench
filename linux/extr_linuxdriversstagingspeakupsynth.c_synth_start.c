#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {TYPE_1__ n; } ;
struct var_t {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  alive; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRIGGER ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct var_t* spk_get_var (int /*<<< orphan*/ ) ; 
 TYPE_3__* synth ; 
 int /*<<< orphan*/  synth_buffer_clear () ; 
 int /*<<< orphan*/  thread_timer ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

void synth_start(void)
{
	struct var_t *trigger_time;

	if (!synth->alive) {
		synth_buffer_clear();
		return;
	}
	trigger_time = spk_get_var(TRIGGER);
	if (!timer_pending(&thread_timer))
		mod_timer(&thread_timer, jiffies +
			msecs_to_jiffies(trigger_time->u.n.value));
}