#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct obs_source_frame {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; } ;
struct async_delay_data {TYPE_1__ video_frames; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,struct obs_source_frame**,int) ; 
 int /*<<< orphan*/  obs_source_release_frame (int /*<<< orphan*/ *,struct obs_source_frame*) ; 

__attribute__((used)) static void free_video_data(struct async_delay_data *filter,
			    obs_source_t *parent)
{
	while (filter->video_frames.size) {
		struct obs_source_frame *frame;

		circlebuf_pop_front(&filter->video_frames, &frame,
				    sizeof(struct obs_source_frame *));
		obs_source_release_frame(parent, frame);
	}
}