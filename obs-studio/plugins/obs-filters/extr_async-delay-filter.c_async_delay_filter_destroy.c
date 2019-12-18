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
struct async_delay_data {int /*<<< orphan*/  audio_frames; int /*<<< orphan*/  video_frames; int /*<<< orphan*/  audio_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_audio_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_delay_filter_destroy(void *data)
{
	struct async_delay_data *filter = data;

	free_audio_packet(&filter->audio_output);
	circlebuf_free(&filter->video_frames);
	circlebuf_free(&filter->audio_frames);
	bfree(data);
}