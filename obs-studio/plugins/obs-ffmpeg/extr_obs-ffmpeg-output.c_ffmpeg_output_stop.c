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
typedef  scalar_t__ uint64_t ;
struct ffmpeg_output {scalar_t__ stop_ts; int /*<<< orphan*/  stopping; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffmpeg_output_full_stop (struct ffmpeg_output*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ffmpeg_output_stop(void *data, uint64_t ts)
{
	struct ffmpeg_output *output = data;

	if (output->active) {
		if (ts == 0) {
			ffmpeg_output_full_stop(output);
		} else {
			os_atomic_set_bool(&output->stopping, true);
			output->stop_ts = ts;
		}
	}
}