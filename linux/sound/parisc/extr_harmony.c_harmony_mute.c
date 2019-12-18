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
struct snd_harmony {int /*<<< orphan*/  mixer_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARMONY_GAINCTL ; 
 int /*<<< orphan*/  HARMONY_GAIN_SILENCE ; 
 int /*<<< orphan*/  harmony_wait_for_control (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_write (struct snd_harmony*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
harmony_mute(struct snd_harmony *h)
{
	unsigned long flags;

	spin_lock_irqsave(&h->mixer_lock, flags);
	harmony_wait_for_control(h);
	harmony_write(h, HARMONY_GAINCTL, HARMONY_GAIN_SILENCE);
	spin_unlock_irqrestore(&h->mixer_lock, flags);
}