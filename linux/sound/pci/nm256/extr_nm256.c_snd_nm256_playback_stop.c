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
struct nm256 {int dummy; } ;

/* Variables and functions */
 int NM_AUDIO_MUTE_LEFT ; 
 int /*<<< orphan*/  NM_AUDIO_MUTE_REG ; 
 int NM_AUDIO_MUTE_RIGHT ; 
 int /*<<< orphan*/  NM_PLAYBACK_ENABLE_REG ; 
 int /*<<< orphan*/  snd_nm256_writeb (struct nm256*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_nm256_writew (struct nm256*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
snd_nm256_playback_stop(struct nm256 *chip)
{
	/* Shut off sound from both channels. */
	snd_nm256_writew(chip, NM_AUDIO_MUTE_REG,
			 NM_AUDIO_MUTE_LEFT | NM_AUDIO_MUTE_RIGHT);
	/* Disable play engine. */
	snd_nm256_writeb(chip, NM_PLAYBACK_ENABLE_REG, 0);
}