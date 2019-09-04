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
struct snd_ac97 {int flags; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int AC97_HAS_NO_CD ; 
 int AC97_HAS_NO_MIC ; 
 int AC97_HAS_NO_PC_BEEP ; 
 int AC97_HAS_NO_REC_GAIN ; 
 int AC97_HAS_NO_VIDEO ; 
 int AC97_STEREO_MUTES ; 
 int /*<<< orphan*/  patch_wolfson_wm9711_ops ; 

__attribute__((used)) static int patch_wolfson11(struct snd_ac97 * ac97)
{
	/* WM9711, WM9712 */
	ac97->build_ops = &patch_wolfson_wm9711_ops;

	ac97->flags |= AC97_HAS_NO_REC_GAIN | AC97_STEREO_MUTES | AC97_HAS_NO_MIC |
		AC97_HAS_NO_PC_BEEP | AC97_HAS_NO_VIDEO | AC97_HAS_NO_CD;
	
	return 0;
}