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
struct hdac_cea_channel_speaker_allocation {int ca_index; int channels; } ;

/* Variables and functions */
 int SNDRV_CTL_TLVT_CHMAP_FIXED ; 
 int SNDRV_CTL_TLVT_CHMAP_VAR ; 

__attribute__((used)) static int nvhdmi_chmap_cea_alloc_validate_get_type(struct hdac_chmap *chmap,
		struct hdac_cea_channel_speaker_allocation *cap, int channels)
{
	if (cap->ca_index == 0x00 && channels == 2)
		return SNDRV_CTL_TLVT_CHMAP_FIXED;

	/* If the speaker allocation matches the channel count, it is OK. */
	if (cap->channels != channels)
		return -1;

	/* all channels are remappable freely */
	return SNDRV_CTL_TLVT_CHMAP_VAR;
}