#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int cs8403_stream_bits; TYPE_1__* stream_ctl; } ;
struct snd_ice1712 {TYPE_2__ spdif; int /*<<< orphan*/  card; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ice1712_delta_cs8403_spdif_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void delta_setup_spdif(struct snd_ice1712 *ice, int rate)
{
	unsigned long flags;
	unsigned int tmp;
	int change;

	spin_lock_irqsave(&ice->reg_lock, flags);
	tmp = ice->spdif.cs8403_stream_bits;
	if (tmp & 0x01)		/* consumer */
		tmp &= (tmp & 0x01) ? ~0x06 : ~0x18;
	switch (rate) {
	case 32000: tmp |= (tmp & 0x01) ? 0x04 : 0x00; break;
	case 44100: tmp |= (tmp & 0x01) ? 0x00 : 0x10; break;
	case 48000: tmp |= (tmp & 0x01) ? 0x02 : 0x08; break;
	default: tmp |= (tmp & 0x01) ? 0x00 : 0x18; break;
	}
	change = ice->spdif.cs8403_stream_bits != tmp;
	ice->spdif.cs8403_stream_bits = tmp;
	spin_unlock_irqrestore(&ice->reg_lock, flags);
	if (change)
		snd_ctl_notify(ice->card, SNDRV_CTL_EVENT_MASK_VALUE, &ice->spdif.stream_ctl->id);
	snd_ice1712_delta_cs8403_spdif_write(ice, tmp);
}