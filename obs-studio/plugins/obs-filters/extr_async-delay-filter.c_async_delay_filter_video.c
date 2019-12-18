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
struct obs_source_frame {scalar_t__ timestamp; } ;
struct async_delay_data {int reset_video; scalar_t__ last_video_ts; int video_delay_reached; scalar_t__ interval; int /*<<< orphan*/  video_frames; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_peek_front (int /*<<< orphan*/ *,struct obs_source_frame**,int) ; 
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,struct obs_source_frame**,int) ; 
 int /*<<< orphan*/  free_video_data (struct async_delay_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_timestamp_jump (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * obs_filter_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct obs_source_frame *
async_delay_filter_video(void *data, struct obs_source_frame *frame)
{
	struct async_delay_data *filter = data;
	obs_source_t *parent = obs_filter_get_parent(filter->context);
	struct obs_source_frame *output;
	uint64_t cur_interval;

	if (filter->reset_video ||
	    is_timestamp_jump(frame->timestamp, filter->last_video_ts)) {
		free_video_data(filter, parent);
		filter->video_delay_reached = false;
		filter->reset_video = false;
	}

	filter->last_video_ts = frame->timestamp;

	circlebuf_push_back(&filter->video_frames, &frame,
			    sizeof(struct obs_source_frame *));
	circlebuf_peek_front(&filter->video_frames, &output,
			     sizeof(struct obs_source_frame *));

	cur_interval = frame->timestamp - output->timestamp;
	if (!filter->video_delay_reached && cur_interval < filter->interval)
		return NULL;

	circlebuf_pop_front(&filter->video_frames, NULL,
			    sizeof(struct obs_source_frame *));

	if (!filter->video_delay_reached)
		filter->video_delay_reached = true;

	return output;
}