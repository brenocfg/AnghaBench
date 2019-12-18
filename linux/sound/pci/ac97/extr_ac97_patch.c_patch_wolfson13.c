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
struct snd_ac97 {int flags; int /*<<< orphan*/  scaps; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_MID ; 
 int /*<<< orphan*/  AC97_EXTENDED_MSTATUS ; 
 int AC97_HAS_NO_CD ; 
 int AC97_HAS_NO_PC_BEEP ; 
 int AC97_HAS_NO_PHONE ; 
 int AC97_HAS_NO_REC_GAIN ; 
 int AC97_HAS_NO_STD_PCM ; 
 int AC97_HAS_NO_TONE ; 
 int AC97_HAS_NO_VIDEO ; 
 int /*<<< orphan*/  AC97_POWERDOWN ; 
 int /*<<< orphan*/  AC97_SCAP_MODEM ; 
 int AC97_STEREO_MUTES ; 
 int /*<<< orphan*/  patch_wolfson_wm9713_ops ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_wolfson13(struct snd_ac97 * ac97)
{
	/* WM9713, WM9714 */
	ac97->build_ops = &patch_wolfson_wm9713_ops;

	ac97->flags |= AC97_HAS_NO_REC_GAIN | AC97_STEREO_MUTES | AC97_HAS_NO_PHONE |
		AC97_HAS_NO_PC_BEEP | AC97_HAS_NO_VIDEO | AC97_HAS_NO_CD | AC97_HAS_NO_TONE |
		AC97_HAS_NO_STD_PCM;
    	ac97->scaps &= ~AC97_SCAP_MODEM;

	snd_ac97_write_cache(ac97, AC97_EXTENDED_MID, 0xda00);
	snd_ac97_write_cache(ac97, AC97_EXTENDED_MSTATUS, 0x3810);
	snd_ac97_write_cache(ac97, AC97_POWERDOWN, 0x0);

	return 0;
}