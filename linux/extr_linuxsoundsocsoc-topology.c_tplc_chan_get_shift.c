#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct soc_tplg {int dummy; } ;
struct snd_soc_tplg_channel {int id; int shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_TPLG_MAX_CHAN ; 

__attribute__((used)) static int tplc_chan_get_shift(struct soc_tplg *tplg,
	struct snd_soc_tplg_channel *chan, int map)
{
	int i;

	for (i = 0; i < SND_SOC_TPLG_MAX_CHAN; i++) {
		if (chan[i].id == map)
			return chan[i].shift;
	}

	return -EINVAL;
}