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
struct hdac_chmap {int dummy; } ;
struct hdac_cea_channel_speaker_allocation {int* speakers; } ;

/* Variables and functions */
 int EINVAL ; 
 int atihdmi_paired_swap_fc_lfe (int) ; 
 int snd_hdac_chmap_to_spk_mask (unsigned char) ; 
 struct hdac_cea_channel_speaker_allocation* snd_hdac_get_ch_alloc_from_ca (int) ; 

__attribute__((used)) static int atihdmi_paired_chmap_validate(struct hdac_chmap *chmap,
			int ca, int chs, unsigned char *map)
{
	struct hdac_cea_channel_speaker_allocation *cap;
	int i, j;

	/* check that only channel pairs need to be remapped on old pre-rev3 ATI/AMD */

	cap = snd_hdac_get_ch_alloc_from_ca(ca);
	for (i = 0; i < chs; ++i) {
		int mask = snd_hdac_chmap_to_spk_mask(map[i]);
		bool ok = false;
		bool companion_ok = false;

		if (!mask)
			continue;

		for (j = 0 + i % 2; j < 8; j += 2) {
			int chan_idx = 7 - atihdmi_paired_swap_fc_lfe(j);
			if (cap->speakers[chan_idx] == mask) {
				/* channel is in a supported position */
				ok = true;

				if (i % 2 == 0 && i + 1 < chs) {
					/* even channel, check the odd companion */
					int comp_chan_idx = 7 - atihdmi_paired_swap_fc_lfe(j + 1);
					int comp_mask_req = snd_hdac_chmap_to_spk_mask(map[i+1]);
					int comp_mask_act = cap->speakers[comp_chan_idx];

					if (comp_mask_req == comp_mask_act)
						companion_ok = true;
					else
						return -EINVAL;
				}
				break;
			}
		}

		if (!ok)
			return -EINVAL;

		if (companion_ok)
			i++; /* companion channel already checked */
	}

	return 0;
}