#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hdsp {int state; scalar_t__ io_type; int /*<<< orphan*/  midi_tasklet; scalar_t__ use_midi_tasklet; TYPE_3__* midi; int /*<<< orphan*/  control_register; TYPE_2__* pcm; scalar_t__ playback_substream; scalar_t__ capture_substream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int pending; } ;
struct TYPE_5__ {TYPE_1__* streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 scalar_t__ H9632 ; 
 int HDSP_InitializationComplete ; 
 int /*<<< orphan*/  HDSP_Midi0InterruptEnable ; 
 int /*<<< orphan*/  HDSP_Midi1InterruptEnable ; 
 unsigned int HDSP_audioIRQPending ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  HDSP_interruptConfirmation ; 
 unsigned int HDSP_midi0IRQPending ; 
 unsigned int HDSP_midi1IRQPending ; 
 int /*<<< orphan*/  HDSP_midiStatusIn0 ; 
 int /*<<< orphan*/  HDSP_midiStatusIn1 ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ Multiface ; 
 scalar_t__ RPM ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdsp_midi_input_read (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_hdsp_interrupt(int irq, void *dev_id)
{
	struct hdsp *hdsp = (struct hdsp *) dev_id;
	unsigned int status;
	int audio;
	int midi0;
	int midi1;
	unsigned int midi0status;
	unsigned int midi1status;
	int schedule = 0;

	status = hdsp_read(hdsp, HDSP_statusRegister);

	audio = status & HDSP_audioIRQPending;
	midi0 = status & HDSP_midi0IRQPending;
	midi1 = status & HDSP_midi1IRQPending;

	if (!audio && !midi0 && !midi1)
		return IRQ_NONE;

	hdsp_write(hdsp, HDSP_interruptConfirmation, 0);

	midi0status = hdsp_read (hdsp, HDSP_midiStatusIn0) & 0xff;
	midi1status = hdsp_read (hdsp, HDSP_midiStatusIn1) & 0xff;

	if (!(hdsp->state & HDSP_InitializationComplete))
		return IRQ_HANDLED;

	if (audio) {
		if (hdsp->capture_substream)
			snd_pcm_period_elapsed(hdsp->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);

		if (hdsp->playback_substream)
			snd_pcm_period_elapsed(hdsp->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream);
	}

	if (midi0 && midi0status) {
		if (hdsp->use_midi_tasklet) {
			/* we disable interrupts for this input until processing is done */
			hdsp->control_register &= ~HDSP_Midi0InterruptEnable;
			hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);
			hdsp->midi[0].pending = 1;
			schedule = 1;
		} else {
			snd_hdsp_midi_input_read (&hdsp->midi[0]);
		}
	}
	if (hdsp->io_type != Multiface && hdsp->io_type != RPM && hdsp->io_type != H9632 && midi1 && midi1status) {
		if (hdsp->use_midi_tasklet) {
			/* we disable interrupts for this input until processing is done */
			hdsp->control_register &= ~HDSP_Midi1InterruptEnable;
			hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);
			hdsp->midi[1].pending = 1;
			schedule = 1;
		} else {
			snd_hdsp_midi_input_read (&hdsp->midi[1]);
		}
	}
	if (hdsp->use_midi_tasklet && schedule)
		tasklet_schedule(&hdsp->midi_tasklet);
	return IRQ_HANDLED;
}