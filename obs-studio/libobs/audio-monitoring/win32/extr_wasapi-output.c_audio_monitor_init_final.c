#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct audio_monitor {int source_has_video; TYPE_2__* source; scalar_t__ ignore; } ;
struct TYPE_3__ {int output_flags; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 int OBS_SOURCE_VIDEO ; 
 int /*<<< orphan*/  obs_source_add_audio_capture_callback (TYPE_2__*,int /*<<< orphan*/ ,struct audio_monitor*) ; 
 int /*<<< orphan*/  on_audio_playback ; 

__attribute__((used)) static void audio_monitor_init_final(struct audio_monitor *monitor)
{
	if (monitor->ignore)
		return;

	monitor->source_has_video =
		(monitor->source->info.output_flags & OBS_SOURCE_VIDEO) != 0;
	obs_source_add_audio_capture_callback(monitor->source,
					      on_audio_playback, monitor);
}