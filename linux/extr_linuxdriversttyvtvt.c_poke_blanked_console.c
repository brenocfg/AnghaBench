#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* d; } ;
struct TYPE_3__ {scalar_t__ vc_mode; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ KD_GRAPHICS ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  blank_normal_wait ; 
 int /*<<< orphan*/  blank_state ; 
 scalar_t__ blank_timer_expired ; 
 int blankinterval ; 
 scalar_t__ console_blanked ; 
 int /*<<< orphan*/  console_timer ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 size_t fg_console ; 
 scalar_t__ ignore_poke ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  unblank_screen () ; 
 TYPE_2__* vc_cons ; 

void poke_blanked_console(void)
{
	WARN_CONSOLE_UNLOCKED();

	/* Add this so we quickly catch whoever might call us in a non
	 * safe context. Nowadays, unblank_screen() isn't to be called in
	 * atomic contexts and is allowed to schedule (with the special case
	 * of oops_in_progress, but that isn't of any concern for this
	 * function. --BenH.
	 */
	might_sleep();

	/* This isn't perfectly race free, but a race here would be mostly harmless,
	 * at worse, we'll do a spurrious blank and it's unlikely
	 */
	del_timer(&console_timer);
	blank_timer_expired = 0;

	if (ignore_poke || !vc_cons[fg_console].d || vc_cons[fg_console].d->vc_mode == KD_GRAPHICS)
		return;
	if (console_blanked)
		unblank_screen();
	else if (blankinterval) {
		mod_timer(&console_timer, jiffies + (blankinterval * HZ));
		blank_state = blank_normal_wait;
	}
}