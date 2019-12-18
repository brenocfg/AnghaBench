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
struct snd_soc_dai {unsigned int tx_mask; unsigned int rx_mask; TYPE_1__* driver; } ;
struct TYPE_4__ {int (* set_tdm_slot ) (struct snd_soc_dai*,unsigned int,unsigned int,int,int) ;int /*<<< orphan*/  (* xlate_tdm_slot_mask ) (int,unsigned int*,unsigned int*) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  snd_soc_xlate_tdm_slot_mask (int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (int,unsigned int*,unsigned int*) ; 
 int stub2 (struct snd_soc_dai*,unsigned int,unsigned int,int,int) ; 

int snd_soc_dai_set_tdm_slot(struct snd_soc_dai *dai,
			     unsigned int tx_mask, unsigned int rx_mask,
			     int slots, int slot_width)
{
	if (dai->driver->ops->xlate_tdm_slot_mask)
		dai->driver->ops->xlate_tdm_slot_mask(slots,
						      &tx_mask, &rx_mask);
	else
		snd_soc_xlate_tdm_slot_mask(slots, &tx_mask, &rx_mask);

	dai->tx_mask = tx_mask;
	dai->rx_mask = rx_mask;

	if (dai->driver->ops->set_tdm_slot)
		return dai->driver->ops->set_tdm_slot(dai, tx_mask, rx_mask,
						      slots, slot_width);
	else
		return -ENOTSUPP;
}