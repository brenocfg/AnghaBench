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
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int snd_hdac_spk_to_chmap (int) ; 

__attribute__((used)) static void hdmi_cea_alloc_to_tlv_chmap(struct hdac_chmap *hchmap,
		struct hdac_cea_channel_speaker_allocation *cap,
		unsigned int *chmap, int channels)
{
	int count = 0;
	int c;

	for (c = 7; c >= 0; c--) {
		int spk = cap->speakers[c];

		if (!spk)
			continue;

		chmap[count++] = snd_hdac_spk_to_chmap(spk);
	}

	WARN_ON(count != channels);
}