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
struct hdac_cea_channel_speaker_allocation {scalar_t__* speakers; } ;

/* Variables and functions */
 int SNDRV_CTL_TLVT_CHMAP_PAIRED ; 

__attribute__((used)) static int atihdmi_paired_chmap_cea_alloc_validate_get_type(
		struct hdac_chmap *chmap,
		struct hdac_cea_channel_speaker_allocation *cap,
		int channels)
{
	int c;

	/*
	 * Pre-rev3 ATI/AMD codecs operate in a paired channel mode, so
	 * we need to take that into account (a single channel may take 2
	 * channel slots if we need to carry a silent channel next to it).
	 * On Rev3+ AMD codecs this function is not used.
	 */
	int chanpairs = 0;

	/* We only produce even-numbered channel count TLVs */
	if ((channels % 2) != 0)
		return -1;

	for (c = 0; c < 7; c += 2) {
		if (cap->speakers[c] || cap->speakers[c+1])
			chanpairs++;
	}

	if (chanpairs * 2 != channels)
		return -1;

	return SNDRV_CTL_TLVT_CHMAP_PAIRED;
}