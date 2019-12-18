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
struct snd_soc_dai_link {int symmetric_rates; int symmetric_channels; int symmetric_samplebits; int ignore_suspend; } ;

/* Variables and functions */
 unsigned int SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_CHANNELS ; 
 unsigned int SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_RATES ; 
 unsigned int SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_SAMPLEBITS ; 
 unsigned int SND_SOC_TPLG_LNK_FLGBIT_VOICE_WAKEUP ; 

__attribute__((used)) static void set_link_flags(struct snd_soc_dai_link *link,
		unsigned int flag_mask, unsigned int flags)
{
	if (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_RATES)
		link->symmetric_rates =
			flags & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_RATES ? 1 : 0;

	if (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_CHANNELS)
		link->symmetric_channels =
			flags & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_CHANNELS ?
			1 : 0;

	if (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_SAMPLEBITS)
		link->symmetric_samplebits =
			flags & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_SAMPLEBITS ?
			1 : 0;

	if (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_VOICE_WAKEUP)
		link->ignore_suspend =
		flags & SND_SOC_TPLG_LNK_FLGBIT_VOICE_WAKEUP ?
		1 : 0;
}