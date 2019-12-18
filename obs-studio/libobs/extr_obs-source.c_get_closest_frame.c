#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct obs_source_frame {int /*<<< orphan*/  timestamp; } ;
struct TYPE_6__ {struct obs_source_frame** array; int /*<<< orphan*/  num; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_frame_ts; TYPE_4__ async_frames; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase (TYPE_4__,int /*<<< orphan*/ ) ; 
 scalar_t__ ready_async_frame (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct obs_source_frame *get_closest_frame(obs_source_t *source,
							 uint64_t sys_time)
{
	if (!source->async_frames.num)
		return NULL;

	if (!source->last_frame_ts || ready_async_frame(source, sys_time)) {
		struct obs_source_frame *frame = source->async_frames.array[0];
		da_erase(source->async_frames, 0);

		if (!source->last_frame_ts)
			source->last_frame_ts = frame->timestamp;

		return frame;
	}

	return NULL;
}