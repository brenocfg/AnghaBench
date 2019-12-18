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
struct ffmpeg_output {int connecting; int /*<<< orphan*/  start_thread; scalar_t__ total_bytes; scalar_t__ video_start_ts; scalar_t__ audio_start_ts; int /*<<< orphan*/  stopping; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ffmpeg_output*) ; 
 int /*<<< orphan*/  start_thread ; 

__attribute__((used)) static bool ffmpeg_output_start(void *data)
{
	struct ffmpeg_output *output = data;
	int ret;

	if (output->connecting)
		return false;

	os_atomic_set_bool(&output->stopping, false);
	output->audio_start_ts = 0;
	output->video_start_ts = 0;
	output->total_bytes = 0;

	ret = pthread_create(&output->start_thread, NULL, start_thread, output);
	return (output->connecting = (ret == 0));
}