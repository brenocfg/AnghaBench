#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * cur_async_frame; int /*<<< orphan*/ * prev_async_frame; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  deinterlace_get_closest_frames (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_async_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 

void deinterlace_process_last_frame(obs_source_t *s, uint64_t sys_time)
{
	if (s->prev_async_frame) {
		remove_async_frame(s, s->prev_async_frame);
		s->prev_async_frame = NULL;
	}
	if (s->cur_async_frame) {
		remove_async_frame(s, s->cur_async_frame);
		s->cur_async_frame = NULL;
	}

	deinterlace_get_closest_frames(s, sys_time);
}