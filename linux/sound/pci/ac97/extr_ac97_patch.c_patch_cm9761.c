#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned short dev_flags; } ;
struct snd_ac97 {scalar_t__ id; TYPE_1__ spec; int /*<<< orphan*/ * rates; int /*<<< orphan*/  ext_id; int /*<<< orphan*/ * build_ops; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int AC97_CM9761_MULTI_CHAN ; 
 int AC97_CM9761_SPDIF_CTRL ; 
 int /*<<< orphan*/  AC97_EI_SPDIF ; 
 int AC97_EXTENDED_STATUS ; 
 int /*<<< orphan*/  AC97_HAS_NO_PCM_VOL ; 
 scalar_t__ AC97_ID_CM9761_82 ; 
 scalar_t__ AC97_ID_CM9761_83 ; 
 int AC97_INT_PAGING ; 
 int AC97_MASTER ; 
 int AC97_PCM ; 
 size_t AC97_RATES_SPDIF ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_48000 ; 
 int /*<<< orphan*/  patch_cm9761_ops ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 

__attribute__((used)) static int patch_cm9761(struct snd_ac97 *ac97)
{
	unsigned short val;

	/* CM9761 has no PCM volume although the register reacts */
	/* Master volume seems to have _some_ influence on the analog
	 * input sounds
	 */
	ac97->flags |= /*AC97_HAS_NO_MASTER_VOL |*/ AC97_HAS_NO_PCM_VOL;
	snd_ac97_write_cache(ac97, AC97_MASTER, 0x8808);
	snd_ac97_write_cache(ac97, AC97_PCM, 0x8808);

	ac97->spec.dev_flags = 0; /* 1 = model 82 revision B, 2 = model 83 */
	if (ac97->id == AC97_ID_CM9761_82) {
		unsigned short tmp;
		/* check page 1, reg 0x60 */
		val = snd_ac97_read(ac97, AC97_INT_PAGING);
		snd_ac97_write_cache(ac97, AC97_INT_PAGING, (val & ~0x0f) | 0x01);
		tmp = snd_ac97_read(ac97, 0x60);
		ac97->spec.dev_flags = tmp & 1; /* revision B? */
		snd_ac97_write_cache(ac97, AC97_INT_PAGING, val);
	} else if (ac97->id == AC97_ID_CM9761_83)
		ac97->spec.dev_flags = 2;

	ac97->build_ops = &patch_cm9761_ops;

	/* enable spdif */
	/* force the SPDIF bit in ext_id - codec doesn't set this bit! */
        ac97->ext_id |= AC97_EI_SPDIF;
	/* to be sure: we overwrite the ext status bits */
	snd_ac97_write_cache(ac97, AC97_EXTENDED_STATUS, 0x05c0);
	/* Don't set 0x0200 here.  This results in the silent analog output */
	snd_ac97_write_cache(ac97, AC97_CM9761_SPDIF_CTRL, 0x0001); /* enable spdif-in */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */

	/* set-up multi channel */
	/* bit 15: pc master beep off
	 * bit 14: pin47 = EAPD/SPDIF
	 * bit 13: vref ctl [= cm9739]
	 * bit 12: CLFE control (reverted on rev B)
	 * bit 11: Mic/center share (reverted on rev B)
	 * bit 10: suddound/line share
	 * bit  9: Analog-in mix -> surround
	 * bit  8: Analog-in mix -> CLFE
	 * bit  7: Mic/LFE share (mic/center/lfe)
	 * bit  5: vref select (9761A)
	 * bit  4: front control
	 * bit  3: surround control (revereted with rev B)
	 * bit  2: front mic
	 * bit  1: stereo mic
	 * bit  0: mic boost level (0=20dB, 1=30dB)
	 */

#if 0
	if (ac97->spec.dev_flags)
		val = 0x0214;
	else
		val = 0x321c;
#endif
	val = snd_ac97_read(ac97, AC97_CM9761_MULTI_CHAN);
	val |= (1 << 4); /* front on */
	snd_ac97_write_cache(ac97, AC97_CM9761_MULTI_CHAN, val);

	/* FIXME: set up GPIO */
	snd_ac97_write_cache(ac97, 0x70, 0x0100);
	snd_ac97_write_cache(ac97, 0x72, 0x0020);

	return 0;
}