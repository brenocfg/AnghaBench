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
struct snd_trident {scalar_t__ device; int /*<<< orphan*/  reg_lock; TYPE_1__* card; int /*<<< orphan*/  ac97_detect; } ;
struct snd_ac97 {scalar_t__ num; struct snd_trident* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short DX_AC97_BUSY_READ ; 
 unsigned int DX_ACR1_AC97_R ; 
 unsigned short NX_AC97_BUSY_READ ; 
 unsigned int NX_ACR2_AC97_R_PRIMARY ; 
 unsigned int NX_ACR3_AC97_R_SECONDARY ; 
 unsigned short SI_AC97_AUDIO_BUSY ; 
 unsigned short SI_AC97_BUSY_READ ; 
 unsigned int SI_AC97_READ ; 
 unsigned int SI_AC97_SECONDARY ; 
 scalar_t__ TRIDENT_DEVICE_ID_DX ; 
 scalar_t__ TRIDENT_DEVICE_ID_NX ; 
 scalar_t__ TRIDENT_DEVICE_ID_SI7018 ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned short,unsigned int) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned short snd_trident_codec_read(struct snd_ac97 *ac97, unsigned short reg)
{
	unsigned int data = 0, treg;
	unsigned short count = 0xffff;
	unsigned long flags;
	struct snd_trident *trident = ac97->private_data;

	spin_lock_irqsave(&trident->reg_lock, flags);
	if (trident->device == TRIDENT_DEVICE_ID_DX) {
		data = (DX_AC97_BUSY_READ | (reg & 0x000000ff));
		outl(data, TRID_REG(trident, DX_ACR1_AC97_R));
		do {
			data = inl(TRID_REG(trident, DX_ACR1_AC97_R));
			if ((data & DX_AC97_BUSY_READ) == 0)
				break;
		} while (--count);
	} else if (trident->device == TRIDENT_DEVICE_ID_NX) {
		data = (NX_AC97_BUSY_READ | (reg & 0x000000ff));
		treg = ac97->num == 0 ? NX_ACR2_AC97_R_PRIMARY : NX_ACR3_AC97_R_SECONDARY;
		outl(data, TRID_REG(trident, treg));
		do {
			data = inl(TRID_REG(trident, treg));
			if ((data & 0x00000C00) == 0)
				break;
		} while (--count);
	} else if (trident->device == TRIDENT_DEVICE_ID_SI7018) {
		data = SI_AC97_BUSY_READ | SI_AC97_AUDIO_BUSY | (reg & 0x000000ff);
		if (ac97->num == 1)
			data |= SI_AC97_SECONDARY;
		outl(data, TRID_REG(trident, SI_AC97_READ));
		do {
			data = inl(TRID_REG(trident, SI_AC97_READ));
			if ((data & (SI_AC97_BUSY_READ)) == 0)
				break;
		} while (--count);
	}

	if (count == 0 && !trident->ac97_detect) {
		dev_err(trident->card->dev,
			"ac97 codec read TIMEOUT [0x%x/0x%x]!!!\n",
			   reg, data);
		data = 0;
	}

	spin_unlock_irqrestore(&trident->reg_lock, flags);
	return ((unsigned short) (data >> 16));
}