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
struct obs_source_frame {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  full_range; int /*<<< orphan*/  format; } ;
struct obs_source {scalar_t__ async_cache_width; scalar_t__ async_cache_height; int /*<<< orphan*/  async_cache_full_range; int /*<<< orphan*/  async_cache_format; } ;
typedef  enum convert_type { ____Placeholder_convert_type } convert_type ;

/* Variables and functions */
 int get_convert_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool async_texture_changed(struct obs_source *source,
					 const struct obs_source_frame *frame)
{
	enum convert_type prev, cur;
	prev = get_convert_type(source->async_cache_format,
				source->async_cache_full_range);
	cur = get_convert_type(frame->format, frame->full_range);

	return source->async_cache_width != frame->width ||
	       source->async_cache_height != frame->height || prev != cur;
}