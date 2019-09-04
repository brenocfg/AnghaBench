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
struct echoaudio {int midi_full; int /*<<< orphan*/  lock; TYPE_1__* card; int /*<<< orphan*/  timer; scalar_t__ tinuse; int /*<<< orphan*/  midi_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int MIDI_OUT_BUFFER_SIZE ; 
 struct echoaudio* chip ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct echoaudio* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_empty (int /*<<< orphan*/ ) ; 
 int snd_rawmidi_transmit_peek (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 int write_midi (struct echoaudio*,unsigned char*,int) ; 

__attribute__((used)) static void snd_echo_midi_output_write(struct timer_list *t)
{
	struct echoaudio *chip = from_timer(chip, t, timer);
	unsigned long flags;
	int bytes, sent, time;
	unsigned char buf[MIDI_OUT_BUFFER_SIZE - 1];

	/* No interrupts are involved: we have to check at regular intervals
	if the card's output buffer has room for new data. */
	sent = bytes = 0;
	spin_lock_irqsave(&chip->lock, flags);
	chip->midi_full = 0;
	if (!snd_rawmidi_transmit_empty(chip->midi_out)) {
		bytes = snd_rawmidi_transmit_peek(chip->midi_out, buf,
						  MIDI_OUT_BUFFER_SIZE - 1);
		dev_dbg(chip->card->dev, "Try to send %d bytes...\n", bytes);
		sent = write_midi(chip, buf, bytes);
		if (sent < 0) {
			dev_err(chip->card->dev,
				"write_midi() error %d\n", sent);
			/* retry later */
			sent = 9000;
			chip->midi_full = 1;
		} else if (sent > 0) {
			dev_dbg(chip->card->dev, "%d bytes sent\n", sent);
			snd_rawmidi_transmit_ack(chip->midi_out, sent);
		} else {
			/* Buffer is full. DSP's internal buffer is 64 (128 ?)
			bytes long. Let's wait until half of them are sent */
			dev_dbg(chip->card->dev, "Full\n");
			sent = 32;
			chip->midi_full = 1;
		}
	}

	/* We restart the timer only if there is some data left to send */
	if (!snd_rawmidi_transmit_empty(chip->midi_out) && chip->tinuse) {
		/* The timer will expire slightly after the data has been
		   sent */
		time = (sent << 3) / 25 + 1;	/* 8/25=0.32ms to send a byte */
		mod_timer(&chip->timer, jiffies + (time * HZ + 999) / 1000);
		dev_dbg(chip->card->dev,
			"Timer armed(%d)\n", ((time * HZ + 999) / 1000));
	}
	spin_unlock_irqrestore(&chip->lock, flags);
}