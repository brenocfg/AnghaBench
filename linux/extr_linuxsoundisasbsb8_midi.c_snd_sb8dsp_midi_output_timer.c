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
struct snd_sb {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  midi_timer; struct snd_rawmidi_substream* midi_substream_output; } ;
struct snd_rawmidi_substream {int dummy; } ;

/* Variables and functions */
 struct snd_sb* chip ; 
 struct snd_sb* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  midi_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_output_write (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sb8dsp_midi_output_timer(struct timer_list *t)
{
	struct snd_sb *chip = from_timer(chip, t, midi_timer);
	struct snd_rawmidi_substream *substream = chip->midi_substream_output;
	unsigned long flags;

	spin_lock_irqsave(&chip->open_lock, flags);
	mod_timer(&chip->midi_timer, 1 + jiffies);
	spin_unlock_irqrestore(&chip->open_lock, flags);	
	snd_sb8dsp_midi_output_write(substream);
}