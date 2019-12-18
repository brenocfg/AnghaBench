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
struct snd_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; } ;
struct hdsp {scalar_t__ io_type; int system_sample_rate; int playback_pid; int capture_pid; int state; char* card_name; int /*<<< orphan*/  irq; int /*<<< orphan*/  port; int /*<<< orphan*/ * playback_substream; int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 scalar_t__ Digiface ; 
 scalar_t__ H9652 ; 
 int HDSP_InitializationComplete ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_card_register (struct snd_card*) ; 
 int snd_hdsp_create_controls (struct snd_card*,struct hdsp*) ; 
 int snd_hdsp_create_midi (struct snd_card*,struct hdsp*,int) ; 
 int snd_hdsp_create_pcm (struct snd_card*,struct hdsp*) ; 
 int /*<<< orphan*/  snd_hdsp_proc_init (struct hdsp*) ; 
 int snd_hdsp_set_defaults (struct hdsp*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_hdsp_create_alsa_devices(struct snd_card *card, struct hdsp *hdsp)
{
	int err;

	if ((err = snd_hdsp_create_pcm(card, hdsp)) < 0) {
		dev_err(card->dev,
			"Error creating pcm interface\n");
		return err;
	}


	if ((err = snd_hdsp_create_midi(card, hdsp, 0)) < 0) {
		dev_err(card->dev,
			"Error creating first midi interface\n");
		return err;
	}

	if (hdsp->io_type == Digiface || hdsp->io_type == H9652) {
		if ((err = snd_hdsp_create_midi(card, hdsp, 1)) < 0) {
			dev_err(card->dev,
				"Error creating second midi interface\n");
			return err;
		}
	}

	if ((err = snd_hdsp_create_controls(card, hdsp)) < 0) {
		dev_err(card->dev,
			"Error creating ctl interface\n");
		return err;
	}

	snd_hdsp_proc_init(hdsp);

	hdsp->system_sample_rate = -1;
	hdsp->playback_pid = -1;
	hdsp->capture_pid = -1;
	hdsp->capture_substream = NULL;
	hdsp->playback_substream = NULL;

	if ((err = snd_hdsp_set_defaults(hdsp)) < 0) {
		dev_err(card->dev,
			"Error setting default values\n");
		return err;
	}

	if (!(hdsp->state & HDSP_InitializationComplete)) {
		strcpy(card->shortname, "Hammerfall DSP");
		sprintf(card->longname, "%s at 0x%lx, irq %d", hdsp->card_name,
			hdsp->port, hdsp->irq);

		if ((err = snd_card_register(card)) < 0) {
			dev_err(card->dev,
				"error registering card\n");
			return err;
		}
		hdsp->state |= HDSP_InitializationComplete;
	}

	return 0;
}