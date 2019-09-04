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
struct slot {int /*<<< orphan*/ * numid; } ;

/* Variables and functions */
 size_t SNDRV_MIXER_OSS_ITEM_CROUTE ; 
 int /*<<< orphan*/  snd_mixer_oss_put_volume1_sw (struct snd_mixer_oss_file*,struct snd_mixer_oss_slot*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int snd_mixer_oss_put_recsrc1_route(struct snd_mixer_oss_file *fmixer,
					   struct snd_mixer_oss_slot *pslot,
					   int active)
{
	struct slot *slot = pslot->private_data;
	
	snd_mixer_oss_put_volume1_sw(fmixer, pslot, slot->numid[SNDRV_MIXER_OSS_ITEM_CROUTE], active, active, 1);
	return 0;
}