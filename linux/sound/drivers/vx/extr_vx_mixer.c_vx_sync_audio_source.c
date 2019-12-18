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
struct vx_core {scalar_t__ audio_source_target; scalar_t__ audio_source; scalar_t__ pcm_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  vx_change_audio_source (struct vx_core*,scalar_t__) ; 

int vx_sync_audio_source(struct vx_core *chip)
{
	if (chip->audio_source_target == chip->audio_source ||
	    chip->pcm_running)
		return 0;
	vx_change_audio_source(chip, chip->audio_source_target);
	chip->audio_source = chip->audio_source_target;
	return 1;
}