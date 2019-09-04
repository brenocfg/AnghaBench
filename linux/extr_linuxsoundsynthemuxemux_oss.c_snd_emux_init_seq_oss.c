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
struct snd_seq_oss_reg {struct snd_emux* private_data; int /*<<< orphan*/  oper; int /*<<< orphan*/  nvoices; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct snd_seq_device {int /*<<< orphan*/  name; } ;
struct snd_emux {int /*<<< orphan*/  card; int /*<<< orphan*/  max_voices; int /*<<< orphan*/  name; struct snd_seq_device* oss_synth; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAMPLE_TYPE_AWE32 ; 
 struct snd_seq_oss_reg* SNDRV_SEQ_DEVICE_ARGPTR (struct snd_seq_device*) ; 
 int /*<<< orphan*/  SNDRV_SEQ_DEV_ID_OSS ; 
 int /*<<< orphan*/  SYNTH_TYPE_SAMPLE ; 
 int /*<<< orphan*/  oss_callback ; 
 int /*<<< orphan*/  snd_device_register (int /*<<< orphan*/ ,struct snd_seq_device*) ; 
 scalar_t__ snd_seq_device_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct snd_seq_device**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
snd_emux_init_seq_oss(struct snd_emux *emu)
{
	struct snd_seq_oss_reg *arg;
	struct snd_seq_device *dev;

	/* using device#1 here for avoiding conflicts with OPL3 */
	if (snd_seq_device_new(emu->card, 1, SNDRV_SEQ_DEV_ID_OSS,
			       sizeof(struct snd_seq_oss_reg), &dev) < 0)
		return;

	emu->oss_synth = dev;
	strcpy(dev->name, emu->name);
	arg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	arg->type = SYNTH_TYPE_SAMPLE;
	arg->subtype = SAMPLE_TYPE_AWE32;
	arg->nvoices = emu->max_voices;
	arg->oper = oss_callback;
	arg->private_data = emu;

	/* register to OSS synth table */
	snd_device_register(emu->card, dev);
}