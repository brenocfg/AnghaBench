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
struct ff_callbacks {void* frame_free; void* frame_initialize; int /*<<< orphan*/  initialize; int /*<<< orphan*/  format; void* frame; void* opaque; } ;
typedef  int /*<<< orphan*/  ff_callback_initialize ;
typedef  void* ff_callback_frame ;
typedef  int /*<<< orphan*/  ff_callback_format ;

/* Variables and functions */

void ff_demuxer_set_callbacks(struct ff_callbacks *callbacks,
		ff_callback_frame frame,
		ff_callback_format format,
		ff_callback_initialize initialize,
		ff_callback_frame frame_initialize,
		ff_callback_frame frame_free,
		void *opaque)
{
	callbacks->opaque = opaque;
	callbacks->frame = frame;
	callbacks->format = format;
	callbacks->initialize = initialize;
	callbacks->frame_initialize = frame_initialize;
	callbacks->frame_free = frame_free;
}