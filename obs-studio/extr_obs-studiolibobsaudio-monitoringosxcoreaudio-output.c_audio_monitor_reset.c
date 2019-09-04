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
struct audio_monitor {int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  audio_monitor_free (struct audio_monitor*) ; 
 int audio_monitor_init (struct audio_monitor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audio_monitor_init_final (struct audio_monitor*) ; 
 int /*<<< orphan*/  memset (struct audio_monitor*,int /*<<< orphan*/ ,int) ; 

void audio_monitor_reset(struct audio_monitor *monitor)
{
	bool success;

	obs_source_t *source = monitor->source;
	audio_monitor_free(monitor);
	memset(monitor, 0, sizeof(*monitor));

	success = audio_monitor_init(monitor, source);
	if (success)
		audio_monitor_init_final(monitor);
}