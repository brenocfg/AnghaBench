#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hdsp_midi {int /*<<< orphan*/  lock; TYPE_1__* hdsp; scalar_t__ id; scalar_t__ pending; scalar_t__ input; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSP_Midi0InterruptEnable ; 
 int /*<<< orphan*/  HDSP_Midi1InterruptEnable ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  hdsp_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hdsp_midi_input_available (TYPE_1__*,scalar_t__) ; 
 int snd_hdsp_midi_output_write (struct hdsp_midi*) ; 
 unsigned char snd_hdsp_midi_read_byte (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_hdsp_midi_input_read (struct hdsp_midi *hmidi)
{
	unsigned char buf[128]; /* this buffer is designed to match the MIDI input FIFO size */
	unsigned long flags;
	int n_pending;
	int i;

	spin_lock_irqsave (&hmidi->lock, flags);
	if ((n_pending = snd_hdsp_midi_input_available (hmidi->hdsp, hmidi->id)) > 0) {
		if (hmidi->input) {
			if (n_pending > (int)sizeof (buf))
				n_pending = sizeof (buf);
			for (i = 0; i < n_pending; ++i)
				buf[i] = snd_hdsp_midi_read_byte (hmidi->hdsp, hmidi->id);
			if (n_pending)
				snd_rawmidi_receive (hmidi->input, buf, n_pending);
		} else {
			/* flush the MIDI input FIFO */
			while (--n_pending)
				snd_hdsp_midi_read_byte (hmidi->hdsp, hmidi->id);
		}
	}
	hmidi->pending = 0;
	if (hmidi->id)
		hmidi->hdsp->control_register |= HDSP_Midi1InterruptEnable;
	else
		hmidi->hdsp->control_register |= HDSP_Midi0InterruptEnable;
	hdsp_write(hmidi->hdsp, HDSP_controlRegister, hmidi->hdsp->control_register);
	spin_unlock_irqrestore (&hmidi->lock, flags);
	return snd_hdsp_midi_output_write (hmidi);
}