#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num; TYPE_1__** array; } ;
struct TYPE_7__ {TYPE_2__ async_frames; scalar_t__ last_frame_ts; } ;
typedef  TYPE_3__ obs_source_t ;
struct TYPE_5__ {int prev_frame; } ;

/* Variables and functions */

__attribute__((used)) static inline bool first_frame(obs_source_t *s)
{
	if (s->last_frame_ts)
		return false;

	if (s->async_frames.num >= 2)
		s->async_frames.array[0]->prev_frame = true;
	return true;
}