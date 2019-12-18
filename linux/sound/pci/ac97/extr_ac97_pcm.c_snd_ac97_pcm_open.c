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
struct snd_ac97_bus {int** used_slots; TYPE_2__* card; int /*<<< orphan*/  bus_lock; TYPE_3__** codec; } ;
struct ac97_pcm {size_t stream; int cur_dbl; unsigned short aslots; TYPE_1__* r; struct snd_ac97_bus* bus; } ;
typedef  enum ac97_pcm_cfg { ____Placeholder_ac97_pcm_cfg } ac97_pcm_cfg ;
struct TYPE_6__ {int ext_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int* rslots; int /*<<< orphan*/ * codec; } ;

/* Variables and functions */
 int AC97_EI_SPDIF ; 
 int AC97_PCM_CFG_SPDIF ; 
 unsigned char AC97_PCM_FRONT_DAC_RATE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 unsigned char get_slot_reg (struct ac97_pcm*,int,int,int) ; 
 int set_spdif_rate (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  snd_ac97_pcm_close (struct ac97_pcm*) ; 
 int snd_ac97_set_rate (int /*<<< orphan*/ ,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_ac97_pcm_open(struct ac97_pcm *pcm, unsigned int rate,
		      enum ac97_pcm_cfg cfg, unsigned short slots)
{
	struct snd_ac97_bus *bus;
	int i, cidx, r, ok_flag;
	unsigned int reg_ok[4] = {0,0,0,0};
	unsigned char reg;
	int err = 0;

	r = rate > 48000;
	bus = pcm->bus;
	if (cfg == AC97_PCM_CFG_SPDIF) {
		for (cidx = 0; cidx < 4; cidx++)
			if (bus->codec[cidx] && (bus->codec[cidx]->ext_id & AC97_EI_SPDIF)) {
				err = set_spdif_rate(bus->codec[cidx], rate);
				if (err < 0)
					return err;
			}
	}
	spin_lock_irq(&pcm->bus->bus_lock);
	for (i = 3; i < 12; i++) {
		if (!(slots & (1 << i)))
			continue;
		ok_flag = 0;
		for (cidx = 0; cidx < 4; cidx++) {
			if (bus->used_slots[pcm->stream][cidx] & (1 << i)) {
				spin_unlock_irq(&pcm->bus->bus_lock);
				err = -EBUSY;
				goto error;
			}
			if (pcm->r[r].rslots[cidx] & (1 << i)) {
				bus->used_slots[pcm->stream][cidx] |= (1 << i);
				ok_flag++;
			}
		}
		if (!ok_flag) {
			spin_unlock_irq(&pcm->bus->bus_lock);
			dev_err(bus->card->dev,
				"cannot find configuration for AC97 slot %i\n",
				i);
			err = -EAGAIN;
			goto error;
		}
	}
	pcm->cur_dbl = r;
	spin_unlock_irq(&pcm->bus->bus_lock);
	for (i = 3; i < 12; i++) {
		if (!(slots & (1 << i)))
			continue;
		for (cidx = 0; cidx < 4; cidx++) {
			if (pcm->r[r].rslots[cidx] & (1 << i)) {
				reg = get_slot_reg(pcm, cidx, i, r);
				if (reg == 0xff) {
					dev_err(bus->card->dev,
						"invalid AC97 slot %i?\n", i);
					continue;
				}
				if (reg_ok[cidx] & (1 << (reg - AC97_PCM_FRONT_DAC_RATE)))
					continue;
				dev_dbg(bus->card->dev,
					"setting ac97 reg 0x%x to rate %d\n",
					reg, rate);
				err = snd_ac97_set_rate(pcm->r[r].codec[cidx], reg, rate);
				if (err < 0)
					dev_err(bus->card->dev,
						"error in snd_ac97_set_rate: cidx=%d, reg=0x%x, rate=%d, err=%d\n",
						cidx, reg, rate, err);
				else
					reg_ok[cidx] |= (1 << (reg - AC97_PCM_FRONT_DAC_RATE));
			}
		}
	}
	pcm->aslots = slots;
	return 0;

 error:
	pcm->aslots = slots;
	snd_ac97_pcm_close(pcm);
	return err;
}