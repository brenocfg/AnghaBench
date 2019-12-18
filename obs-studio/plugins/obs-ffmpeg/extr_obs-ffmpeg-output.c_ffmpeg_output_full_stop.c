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
struct ffmpeg_output {int /*<<< orphan*/  output; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffmpeg_deactivate (struct ffmpeg_output*) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmpeg_output_full_stop(void *data)
{
	struct ffmpeg_output *output = data;

	if (output->active) {
		obs_output_end_data_capture(output->output);
		ffmpeg_deactivate(output);
	}
}