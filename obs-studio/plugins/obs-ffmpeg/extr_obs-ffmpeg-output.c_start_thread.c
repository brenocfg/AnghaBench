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
struct ffmpeg_output {int connecting; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_OUTPUT_CONNECT_FAILED ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_connect (struct ffmpeg_output*) ; 

__attribute__((used)) static void *start_thread(void *data)
{
	struct ffmpeg_output *output = data;

	if (!try_connect(output))
		obs_output_signal_stop(output->output,
				       OBS_OUTPUT_CONNECT_FAILED);

	output->connecting = false;
	return NULL;
}