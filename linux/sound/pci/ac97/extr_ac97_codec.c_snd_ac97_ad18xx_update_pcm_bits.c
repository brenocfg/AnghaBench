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
struct TYPE_5__ {unsigned short* pcmreg; unsigned short* unchained; unsigned short* chained; } ;
struct TYPE_6__ {TYPE_1__ ad18xx; } ;
struct snd_ac97 {int /*<<< orphan*/  page_mutex; int /*<<< orphan*/  reg_mutex; TYPE_4__* bus; TYPE_2__ spec; } ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* write ) (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_SERIAL_CFG ; 
 int /*<<< orphan*/  AC97_PCM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short snd_ac97_read_cache (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  stub2 (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  stub3 (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int snd_ac97_ad18xx_update_pcm_bits(struct snd_ac97 *ac97, int codec, unsigned short mask, unsigned short value)
{
	int change;
	unsigned short old, new, cfg;

	mutex_lock(&ac97->page_mutex);
	old = ac97->spec.ad18xx.pcmreg[codec];
	new = (old & ~mask) | (value & mask);
	change = old != new;
	if (change) {
		mutex_lock(&ac97->reg_mutex);
		cfg = snd_ac97_read_cache(ac97, AC97_AD_SERIAL_CFG);
		ac97->spec.ad18xx.pcmreg[codec] = new;
		/* select single codec */
		ac97->bus->ops->write(ac97, AC97_AD_SERIAL_CFG,
				 (cfg & ~0x7000) |
				 ac97->spec.ad18xx.unchained[codec] | ac97->spec.ad18xx.chained[codec]);
		/* update PCM bits */
		ac97->bus->ops->write(ac97, AC97_PCM, new);
		/* select all codecs */
		ac97->bus->ops->write(ac97, AC97_AD_SERIAL_CFG,
				 cfg | 0x7000);
		mutex_unlock(&ac97->reg_mutex);
	}
	mutex_unlock(&ac97->page_mutex);
	return change;
}