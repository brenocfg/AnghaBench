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
struct snd_ac97 {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_SERIAL_CFG ; 
 int EINVAL ; 
 int /*<<< orphan*/  ac97_err (struct snd_ac97*,char*) ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int tune_ad_sharing(struct snd_ac97 *ac97)
{
	unsigned short scfg;
	if ((ac97->id & 0xffffff00) != 0x41445300) {
		ac97_err(ac97, "ac97_quirk AD_SHARING is only for AD codecs\n");
		return -EINVAL;
	}
	/* Turn on OMS bit to route microphone to back panel */
	scfg = snd_ac97_read(ac97, AC97_AD_SERIAL_CFG);
	snd_ac97_write_cache(ac97, AC97_AD_SERIAL_CFG, scfg | 0x0200);
	return 0;
}