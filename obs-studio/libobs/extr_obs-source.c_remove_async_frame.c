#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_source_frame {int prev_frame; } ;
struct async_frame {int used; struct obs_source_frame* frame; } ;
struct TYPE_4__ {size_t num; struct async_frame* array; } ;
struct TYPE_5__ {TYPE_1__ async_cache; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */

void remove_async_frame(obs_source_t *source, struct obs_source_frame *frame)
{
	if (frame)
		frame->prev_frame = false;

	for (size_t i = 0; i < source->async_cache.num; i++) {
		struct async_frame *f = &source->async_cache.array[i];

		if (f->frame == frame) {
			f->used = false;
			break;
		}
	}
}