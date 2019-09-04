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
struct snd_azf3328 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_MIXER_RESET ; 
 int /*<<< orphan*/  snd_azf3328_mixer_mute_control_master (struct snd_azf3328 const*,int) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_outw (struct snd_azf3328 const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
snd_azf3328_mixer_reset(const struct snd_azf3328 *chip)
{
	/* reset (close) mixer:
	 * first mute master volume, then reset
	 */
	snd_azf3328_mixer_mute_control_master(chip, 1);
	snd_azf3328_mixer_outw(chip, IDX_MIXER_RESET, 0x0000);
}