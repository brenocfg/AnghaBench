#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_ali_voice {scalar_t__ midi; scalar_t__ synth; scalar_t__ substream; scalar_t__ running; scalar_t__ pcm; } ;
struct TYPE_8__ {unsigned int aint; } ;
struct TYPE_7__ {scalar_t__ aint; } ;
struct snd_ali_channel_control {TYPE_4__ data; TYPE_3__ regs; } ;
struct TYPE_6__ {struct snd_ali_voice* voices; } ;
struct snd_ali {int /*<<< orphan*/  reg_lock; TYPE_2__ synth; TYPE_1__* card; struct snd_ali_channel_control chregs; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALI_CSO_ALPHA_FMS ; 
 scalar_t__ ALI_CSPF ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_disable_voice_irq (struct snd_ali*,int) ; 
 int /*<<< orphan*/  snd_ali_stop_voice (struct snd_ali*,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_ali_update_ptr(struct snd_ali *codec, int channel)
{
	struct snd_ali_voice *pvoice;
	struct snd_ali_channel_control *pchregs;
	unsigned int old, mask;

	pchregs = &(codec->chregs);

	/* check if interrupt occurred for channel */
	old  = pchregs->data.aint;
	mask = 1U << (channel & 0x1f);

	if (!(old & mask))
		return;

	pvoice = &codec->synth.voices[channel];

	udelay(100);
	spin_lock(&codec->reg_lock);

	if (pvoice->pcm && pvoice->substream) {
		/* pcm interrupt */
		if (pvoice->running) {
			dev_dbg(codec->card->dev,
				"update_ptr: cso=%4.4x cspf=%d.\n",
				inw(ALI_REG(codec, ALI_CSO_ALPHA_FMS + 2)),
				(inl(ALI_REG(codec, ALI_CSPF)) & mask) == mask);
			spin_unlock(&codec->reg_lock);
			snd_pcm_period_elapsed(pvoice->substream);
			spin_lock(&codec->reg_lock);
		} else {
			snd_ali_stop_voice(codec, channel);
			snd_ali_disable_voice_irq(codec, channel);
		}	
	} else if (codec->synth.voices[channel].synth) {
		/* synth interrupt */
	} else if (codec->synth.voices[channel].midi) {
		/* midi interrupt */
	} else {
		/* unknown interrupt */
		snd_ali_stop_voice(codec, channel);
		snd_ali_disable_voice_irq(codec, channel);
	}
	spin_unlock(&codec->reg_lock);
	outl(mask,ALI_REG(codec,pchregs->regs.aint));
	pchregs->data.aint = old & (~mask);
}