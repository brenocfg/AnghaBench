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
struct snd_mixer_oss_slot {struct slot* private_data; } ;
struct snd_mixer_oss_file {int dummy; } ;
struct slot {int present; int /*<<< orphan*/ * numid; } ;

/* Variables and functions */
 size_t SNDRV_MIXER_OSS_ITEM_GLOBAL ; 
 size_t SNDRV_MIXER_OSS_ITEM_GROUTE ; 
 size_t SNDRV_MIXER_OSS_ITEM_GSWITCH ; 
 size_t SNDRV_MIXER_OSS_ITEM_GVOLUME ; 
 size_t SNDRV_MIXER_OSS_ITEM_PROUTE ; 
 size_t SNDRV_MIXER_OSS_ITEM_PSWITCH ; 
 size_t SNDRV_MIXER_OSS_ITEM_PVOLUME ; 
 int SNDRV_MIXER_OSS_PRESENT_GLOBAL ; 
 int SNDRV_MIXER_OSS_PRESENT_GROUTE ; 
 int SNDRV_MIXER_OSS_PRESENT_GSWITCH ; 
 int SNDRV_MIXER_OSS_PRESENT_GVOLUME ; 
 int SNDRV_MIXER_OSS_PRESENT_PROUTE ; 
 int SNDRV_MIXER_OSS_PRESENT_PSWITCH ; 
 int SNDRV_MIXER_OSS_PRESENT_PVOLUME ; 
 int /*<<< orphan*/  snd_mixer_oss_get_volume1_sw (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  snd_mixer_oss_get_volume1_vol (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int snd_mixer_oss_get_volume1(struct snd_mixer_oss_file *fmixer,
				     struct snd_mixer_oss_slot *pslot,
				     int *left, int *right)
{
	struct slot *slot = pslot->private_data;
	
	*left = *right = 100;
	if (slot->present & SNDRV_MIXER_OSS_PRESENT_PVOLUME) {
		snd_mixer_oss_get_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PVOLUME], left, right);
	} else if (slot->present & SNDRV_MIXER_OSS_PRESENT_GVOLUME) {
		snd_mixer_oss_get_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GVOLUME], left, right);
	} else if (slot->present & SNDRV_MIXER_OSS_PRESENT_GLOBAL) {
		snd_mixer_oss_get_volume1_vol(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GLOBAL], left, right);
	}
	if (slot->present & SNDRV_MIXER_OSS_PRESENT_PSWITCH) {
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PSWITCH], left, right, 0);
	} else if (slot->present & SNDRV_MIXER_OSS_PRESENT_GSWITCH) {
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GSWITCH], left, right, 0);
	} else if (slot->present & SNDRV_MIXER_OSS_PRESENT_PROUTE) {
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_PROUTE], left, right, 1);
	} else if (slot->present & SNDRV_MIXER_OSS_PRESENT_GROUTE) {
		snd_mixer_oss_get_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_GROUTE], left, right, 1);
	}
	return 0;
}