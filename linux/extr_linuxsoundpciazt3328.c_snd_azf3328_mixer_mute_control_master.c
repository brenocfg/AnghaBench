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
 int /*<<< orphan*/  IDX_MIXER_PLAY_MASTER ; 
 int snd_azf3328_mixer_mute_control (struct snd_azf3328 const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool
snd_azf3328_mixer_mute_control_master(const struct snd_azf3328 *chip,
			   bool do_mute
)
{
	return snd_azf3328_mixer_mute_control(
		chip,
		IDX_MIXER_PLAY_MASTER,
		do_mute
	);
}