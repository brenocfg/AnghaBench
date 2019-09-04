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
struct obs_source_frame {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
struct TYPE_5__ {TYPE_1__* async_preload_frame; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;

/* Variables and functions */

__attribute__((used)) static inline bool preload_frame_changed(obs_source_t *source,
		const struct obs_source_frame *in)
{
	if (!source->async_preload_frame)
		return true;

	return in->width  != source->async_preload_frame->width  ||
	       in->height != source->async_preload_frame->height ||
	       in->format != source->async_preload_frame->format;
}