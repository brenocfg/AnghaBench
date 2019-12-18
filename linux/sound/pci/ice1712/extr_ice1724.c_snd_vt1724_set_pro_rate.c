#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* setup_rate ) (struct snd_ice1712*,unsigned int) ;} ;
struct TYPE_11__ {TYPE_4__ ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_pro_rate ) (struct snd_ice1712*,unsigned int) ;int /*<<< orphan*/  (* i2s_mclk_changed ) (struct snd_ice1712*) ;} ;
struct snd_ice1712 {unsigned int cur_rate; unsigned int (* get_rate ) (struct snd_ice1712*) ;unsigned char (* set_mclk ) (struct snd_ice1712*,unsigned int) ;unsigned int akm_codecs; TYPE_5__ spdif; TYPE_6__* akm; TYPE_2__ gpio; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  (* set_rate ) (struct snd_ice1712*,unsigned int) ;int /*<<< orphan*/  (* is_spdif_master ) (struct snd_ice1712*) ;TYPE_1__* hw_rates; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_rate_val ) (TYPE_6__*,unsigned int) ;} ;
struct TYPE_12__ {TYPE_3__ ops; } ;
struct TYPE_7__ {unsigned int* list; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CONTROL ; 
 int /*<<< orphan*/  DMA_PAUSE ; 
 int DMA_PAUSES ; 
 int DMA_STARTS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 scalar_t__ is_pro_rate_locked (struct snd_ice1712*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*) ; 
 unsigned int stub2 (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stub3 (struct snd_ice1712*,unsigned int) ; 
 unsigned char stub4 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub5 (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stub6 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,unsigned int) ; 
 int /*<<< orphan*/  stub8 (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static int snd_vt1724_set_pro_rate(struct snd_ice1712 *ice, unsigned int rate,
				    int force)
{
	unsigned long flags;
	unsigned char mclk_change;
	unsigned int i, old_rate;

	if (rate > ice->hw_rates->list[ice->hw_rates->count - 1])
		return -EINVAL;

	spin_lock_irqsave(&ice->reg_lock, flags);
	if ((inb(ICEMT1724(ice, DMA_CONTROL)) & DMA_STARTS) ||
	    (inb(ICEMT1724(ice, DMA_PAUSE)) & DMA_PAUSES)) {
		/* running? we cannot change the rate now... */
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		return ((rate == ice->cur_rate) && !force) ? 0 : -EBUSY;
	}
	if (!force && is_pro_rate_locked(ice)) {
		/* comparing required and current rate - makes sense for
		 * internal clock only */
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		return (rate == ice->cur_rate) ? 0 : -EBUSY;
	}

	if (force || !ice->is_spdif_master(ice)) {
		/* force means the rate was switched by ucontrol, otherwise
		 * setting clock rate for internal clock mode */
		old_rate = ice->get_rate(ice);
		if (force || (old_rate != rate))
			ice->set_rate(ice, rate);
		else if (rate == ice->cur_rate) {
			spin_unlock_irqrestore(&ice->reg_lock, flags);
			return 0;
		}
	}

	ice->cur_rate = rate;

	/* setting master clock */
	mclk_change = ice->set_mclk(ice, rate);

	spin_unlock_irqrestore(&ice->reg_lock, flags);

	if (mclk_change && ice->gpio.i2s_mclk_changed)
		ice->gpio.i2s_mclk_changed(ice);
	if (ice->gpio.set_pro_rate)
		ice->gpio.set_pro_rate(ice, rate);

	/* set up codecs */
	for (i = 0; i < ice->akm_codecs; i++) {
		if (ice->akm[i].ops.set_rate_val)
			ice->akm[i].ops.set_rate_val(&ice->akm[i], rate);
	}
	if (ice->spdif.ops.setup_rate)
		ice->spdif.ops.setup_rate(ice, rate);

	return 0;
}