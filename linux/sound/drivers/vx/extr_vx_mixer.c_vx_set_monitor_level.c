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
struct vx_core {int* audio_monitor; int* audio_monitor_active; } ;
struct vx_audio_level {int has_monitor_level; int monitor_level; int has_monitor_mute; int monitor_mute; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vx_audio_level*,int /*<<< orphan*/ ,int) ; 
 int vx_adjust_audio_level (struct vx_core*,int,int /*<<< orphan*/ ,struct vx_audio_level*) ; 

int vx_set_monitor_level(struct vx_core *chip, int audio, int level, int active)
{
	struct vx_audio_level info;

	memset(&info, 0, sizeof(info));
	info.has_monitor_level = 1;
	info.monitor_level = level;
	info.has_monitor_mute = 1;
	info.monitor_mute = !active;
	chip->audio_monitor[audio] = level;
	chip->audio_monitor_active[audio] = active;
	return vx_adjust_audio_level(chip, audio, 0, &info); /* playback only */
}