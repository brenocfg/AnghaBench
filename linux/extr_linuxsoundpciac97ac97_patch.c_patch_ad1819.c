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
struct snd_ac97 {int /*<<< orphan*/  res_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_SERIAL_CFG ; 
 int /*<<< orphan*/  ad1819_restbl ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int patch_ad1819(struct snd_ac97 * ac97)
{
	unsigned short scfg;

	// patch for Analog Devices
	scfg = snd_ac97_read(ac97, AC97_AD_SERIAL_CFG);
	snd_ac97_write_cache(ac97, AC97_AD_SERIAL_CFG, scfg | 0x7000); /* select all codecs */
	ac97->res_table = ad1819_restbl;
	return 0;
}