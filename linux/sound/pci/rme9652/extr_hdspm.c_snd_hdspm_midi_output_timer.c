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
struct hdspm_midi {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; scalar_t__ istimer; } ;

/* Variables and functions */
 struct hdspm_midi* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hdspm_midi* hmidi ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_hdspm_midi_output_write (struct hdspm_midi*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void snd_hdspm_midi_output_timer(struct timer_list *t)
{
	struct hdspm_midi *hmidi = from_timer(hmidi, t, timer);
	unsigned long flags;

	snd_hdspm_midi_output_write(hmidi);
	spin_lock_irqsave (&hmidi->lock, flags);

	/* this does not bump hmidi->istimer, because the
	   kernel automatically removed the timer when it
	   expired, and we are now adding it back, thus
	   leaving istimer wherever it was set before.
	*/

	if (hmidi->istimer)
		mod_timer(&hmidi->timer, 1 + jiffies);

	spin_unlock_irqrestore (&hmidi->lock, flags);
}