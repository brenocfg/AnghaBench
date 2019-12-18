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
struct TYPE_2__ {int /*<<< orphan*/  gain; } ;
struct snd_harmony {int /*<<< orphan*/  mixer_lock; TYPE_1__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARMONY_GAINCTL ; 
 int /*<<< orphan*/  harmony_wait_for_control (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_write (struct snd_harmony*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
harmony_unmute(struct snd_harmony *h)
{
	unsigned long flags;

	spin_lock_irqsave(&h->mixer_lock, flags);
	harmony_wait_for_control(h);
	harmony_write(h, HARMONY_GAINCTL, h->st.gain);
	spin_unlock_irqrestore(&h->mixer_lock, flags);
}