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
struct hdspm {int midiPorts; int /*<<< orphan*/  midi_tasklet; TYPE_1__* midi; int /*<<< orphan*/  control_register; scalar_t__ playback_substream; scalar_t__ capture_substream; int /*<<< orphan*/  irq_count; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned int irq; int pending; int /*<<< orphan*/  ie; int /*<<< orphan*/  statusIn; } ;

/* Variables and functions */
 unsigned int HDSPM_audioIRQPending ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  HDSPM_interruptConfirmation ; 
 unsigned int HDSPM_midi0IRQPending ; 
 unsigned int HDSPM_midi1IRQPending ; 
 unsigned int HDSPM_midi2IRQPending ; 
 unsigned int HDSPM_midi3IRQPending ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_hdspm_interrupt(int irq, void *dev_id)
{
	struct hdspm *hdspm = (struct hdspm *) dev_id;
	unsigned int status;
	int i, audio, midi, schedule = 0;
	/* cycles_t now; */

	status = hdspm_read(hdspm, HDSPM_statusRegister);

	audio = status & HDSPM_audioIRQPending;
	midi = status & (HDSPM_midi0IRQPending | HDSPM_midi1IRQPending |
			HDSPM_midi2IRQPending | HDSPM_midi3IRQPending);

	/* now = get_cycles(); */
	/*
	 *   LAT_2..LAT_0 period  counter (win)  counter (mac)
	 *          6       4096   ~256053425     ~514672358
	 *          5       2048   ~128024983     ~257373821
	 *          4       1024    ~64023706     ~128718089
	 *          3        512    ~32005945      ~64385999
	 *          2        256    ~16003039      ~32260176
	 *          1        128     ~7998738      ~16194507
	 *          0         64     ~3998231       ~8191558
	 */
	/*
	  dev_info(hdspm->card->dev, "snd_hdspm_interrupt %llu @ %llx\n",
	   now-hdspm->last_interrupt, status & 0xFFC0);
	   hdspm->last_interrupt = now;
	*/

	if (!audio && !midi)
		return IRQ_NONE;

	hdspm_write(hdspm, HDSPM_interruptConfirmation, 0);
	hdspm->irq_count++;


	if (audio) {
		if (hdspm->capture_substream)
			snd_pcm_period_elapsed(hdspm->capture_substream);

		if (hdspm->playback_substream)
			snd_pcm_period_elapsed(hdspm->playback_substream);
	}

	if (midi) {
		i = 0;
		while (i < hdspm->midiPorts) {
			if ((hdspm_read(hdspm,
				hdspm->midi[i].statusIn) & 0xff) &&
					(status & hdspm->midi[i].irq)) {
				/* we disable interrupts for this input until
				 * processing is done
				 */
				hdspm->control_register &= ~hdspm->midi[i].ie;
				hdspm_write(hdspm, HDSPM_controlRegister,
						hdspm->control_register);
				hdspm->midi[i].pending = 1;
				schedule = 1;
			}

			i++;
		}

		if (schedule)
			tasklet_hi_schedule(&hdspm->midi_tasklet);
	}

	return IRQ_HANDLED;
}