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
struct snd_soc_dai {int /*<<< orphan*/  component; TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_pll ) (struct snd_soc_dai*,int,int,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int snd_soc_component_set_pll (int /*<<< orphan*/ ,int,int,unsigned int,unsigned int) ; 
 int stub1 (struct snd_soc_dai*,int,int,unsigned int,unsigned int) ; 

int snd_soc_dai_set_pll(struct snd_soc_dai *dai, int pll_id, int source,
			unsigned int freq_in, unsigned int freq_out)
{
	if (dai->driver->ops->set_pll)
		return dai->driver->ops->set_pll(dai, pll_id, source,
						 freq_in, freq_out);

	return snd_soc_component_set_pll(dai->component, pll_id, source,
					 freq_in, freq_out);
}