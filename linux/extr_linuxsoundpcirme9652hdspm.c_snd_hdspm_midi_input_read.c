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
struct hdspm_midi {TYPE_1__* hdspm; int /*<<< orphan*/  ie; int /*<<< orphan*/  lock; scalar_t__ pending; int /*<<< orphan*/  id; scalar_t__ input; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  hdspm_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hdspm_midi_input_available (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int snd_hdspm_midi_output_write (struct hdspm_midi*) ; 
 unsigned char snd_hdspm_midi_read_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_hdspm_midi_input_read (struct hdspm_midi *hmidi)
{
	unsigned char buf[128]; /* this buffer is designed to match the MIDI
				 * input FIFO size
				 */
	unsigned long flags;
	int n_pending;
	int i;

	spin_lock_irqsave (&hmidi->lock, flags);
	n_pending = snd_hdspm_midi_input_available (hmidi->hdspm, hmidi->id);
	if (n_pending > 0) {
		if (hmidi->input) {
			if (n_pending > (int)sizeof (buf))
				n_pending = sizeof (buf);
			for (i = 0; i < n_pending; ++i)
				buf[i] = snd_hdspm_midi_read_byte (hmidi->hdspm,
								   hmidi->id);
			if (n_pending)
				snd_rawmidi_receive (hmidi->input, buf,
						     n_pending);
		} else {
			/* flush the MIDI input FIFO */
			while (n_pending--)
				snd_hdspm_midi_read_byte (hmidi->hdspm,
							  hmidi->id);
		}
	}
	hmidi->pending = 0;
	spin_unlock_irqrestore(&hmidi->lock, flags);

	spin_lock_irqsave(&hmidi->hdspm->lock, flags);
	hmidi->hdspm->control_register |= hmidi->ie;
	hdspm_write(hmidi->hdspm, HDSPM_controlRegister,
		    hmidi->hdspm->control_register);
	spin_unlock_irqrestore(&hmidi->hdspm->lock, flags);

	return snd_hdspm_midi_output_write (hmidi);
}