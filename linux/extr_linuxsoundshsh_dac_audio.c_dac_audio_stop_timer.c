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
struct snd_sh_dac {int /*<<< orphan*/  hrtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dac_audio_stop_timer(struct snd_sh_dac *chip)
{
	hrtimer_cancel(&chip->hrtimer);
}