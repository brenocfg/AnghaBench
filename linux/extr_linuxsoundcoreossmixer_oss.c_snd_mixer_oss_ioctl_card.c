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
struct snd_mixer_oss_file {int /*<<< orphan*/ * mixer; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/ * mixer_oss; } ;
typedef  int /*<<< orphan*/  fmixer ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  memset (struct snd_mixer_oss_file*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_mixer_oss_ioctl1 (struct snd_mixer_oss_file*,unsigned int,unsigned long) ; 

int snd_mixer_oss_ioctl_card(struct snd_card *card, unsigned int cmd, unsigned long arg)
{
	struct snd_mixer_oss_file fmixer;
	
	if (snd_BUG_ON(!card))
		return -ENXIO;
	if (card->mixer_oss == NULL)
		return -ENXIO;
	memset(&fmixer, 0, sizeof(fmixer));
	fmixer.card = card;
	fmixer.mixer = card->mixer_oss;
	return snd_mixer_oss_ioctl1(&fmixer, cmd, arg);
}