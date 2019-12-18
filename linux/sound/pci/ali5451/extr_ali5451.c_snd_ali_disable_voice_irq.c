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
struct TYPE_5__ {int /*<<< orphan*/  ainten; } ;
struct TYPE_4__ {unsigned int ainten; } ;
struct snd_ali_channel_control {TYPE_2__ regs; TYPE_1__ data; } ;
struct snd_ali {TYPE_3__* card; struct snd_ali_channel_control chregs; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ali_disable_voice_irq(struct snd_ali *codec,
				      unsigned int channel)
{
	unsigned int mask;
	struct snd_ali_channel_control *pchregs = &(codec->chregs);

	dev_dbg(codec->card->dev, "disable_voice_irq channel=%d\n", channel);

	mask = 1 << (channel & 0x1f);
	pchregs->data.ainten  = inl(ALI_REG(codec, pchregs->regs.ainten));
	pchregs->data.ainten &= ~mask;
	outl(pchregs->data.ainten, ALI_REG(codec, pchregs->regs.ainten));
}