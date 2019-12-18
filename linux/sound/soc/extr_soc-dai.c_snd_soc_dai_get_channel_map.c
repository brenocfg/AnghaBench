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
struct snd_soc_dai {TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_channel_map ) (struct snd_soc_dai*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct snd_soc_dai*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

int snd_soc_dai_get_channel_map(struct snd_soc_dai *dai,
				unsigned int *tx_num, unsigned int *tx_slot,
				unsigned int *rx_num, unsigned int *rx_slot)
{
	if (dai->driver->ops->get_channel_map)
		return dai->driver->ops->get_channel_map(dai, tx_num, tx_slot,
							 rx_num, rx_slot);
	else
		return -ENOTSUPP;
}