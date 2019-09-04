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
struct snd_opl3 {int /*<<< orphan*/  voice_lock; } ;
struct snd_midi_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_opl3_note_off_unsafe (void*,int,int,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_opl3_note_off(void *p, int note, int vel,
		       struct snd_midi_channel *chan)
{
	struct snd_opl3 *opl3 = p;
	unsigned long flags;

	spin_lock_irqsave(&opl3->voice_lock, flags);
	snd_opl3_note_off_unsafe(p, note, vel, chan);
	spin_unlock_irqrestore(&opl3->voice_lock, flags);
}