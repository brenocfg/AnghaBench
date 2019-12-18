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
typedef  int u8 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int rate; int buffer_size; unsigned int dma_addr; int /*<<< orphan*/  period_size; struct snd_ali_voice* private_data; } ;
struct snd_ali_voice {scalar_t__ number; int eso; int /*<<< orphan*/  count; int /*<<< orphan*/  mode; } ;
struct snd_ali {scalar_t__ revision; int /*<<< orphan*/  reg_lock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALI_5451_V02 ; 
 scalar_t__ ALI_MODEM_IN_CHANNEL ; 
 scalar_t__ ALI_MODEM_OUT_CHANNEL ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALI_SPDIF_CTRL ; 
 scalar_t__ ALI_SPDIF_IN_CHANNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 unsigned int snd_ali_control_mode (struct snd_pcm_substream*) ; 
 int snd_ali_convert_rate (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_enable_special_channel (struct snd_ali*,scalar_t__) ; 
 unsigned int snd_ali_get_spdif_in_rate (struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_write_voice_regs (struct snd_ali*,scalar_t__,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct snd_ali* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ali_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ali *codec = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ali_voice *pvoice = runtime->private_data;
	unsigned int LBA;
	unsigned int Delta;
	unsigned int ESO;
	unsigned int CTRL;
	unsigned int GVSEL;
	unsigned int PAN;
	unsigned int VOL;
	unsigned int EC;
	u8	 bValue;

	spin_lock_irq(&codec->reg_lock);

	dev_dbg(codec->card->dev, "ali_prepare...\n");

	snd_ali_enable_special_channel(codec,pvoice->number);

	Delta = (pvoice->number == ALI_MODEM_IN_CHANNEL ||
		 pvoice->number == ALI_MODEM_OUT_CHANNEL) ? 
		0x1000 : snd_ali_convert_rate(runtime->rate, pvoice->mode);

	/* Prepare capture intr channel */
	if (pvoice->number == ALI_SPDIF_IN_CHANNEL) {

		unsigned int rate;
		
		spin_unlock_irq(&codec->reg_lock);
		if (codec->revision != ALI_5451_V02)
			return -1;

		rate = snd_ali_get_spdif_in_rate(codec);
		if (rate == 0) {
			dev_warn(codec->card->dev,
				 "ali_capture_prepare: spdif rate detect err!\n");
			rate = 48000;
		}
		spin_lock_irq(&codec->reg_lock);
		bValue = inb(ALI_REG(codec,ALI_SPDIF_CTRL));
		if (bValue & 0x10) {
			outb(bValue,ALI_REG(codec,ALI_SPDIF_CTRL));
			dev_warn(codec->card->dev,
				 "clear SPDIF parity error flag.\n");
		}

		if (rate != 48000)
			Delta = ((rate << 12) / runtime->rate) & 0x00ffff;
	}

	/* set target ESO for channel  */
	pvoice->eso = runtime->buffer_size; 

	/* set interrupt count size  */
	pvoice->count = runtime->period_size;

	/* set Loop Back Address  */
	LBA = runtime->dma_addr;

	/* set ESO to capture first MIDLP interrupt  */
	ESO = pvoice->eso - 1;
	CTRL = snd_ali_control_mode(substream);
	GVSEL = 0;
	PAN = 0x00;
	VOL = 0x00;
	EC = 0;

	snd_ali_write_voice_regs(    codec,
				     pvoice->number,
				     LBA,
				     0,	/* cso */
				     ESO,
				     Delta,
				     0,	/* alpha */
				     GVSEL,
				     PAN,
				     VOL,
				     CTRL,
				     EC);

	spin_unlock_irq(&codec->reg_lock);

	return 0;
}