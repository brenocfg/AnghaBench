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
struct TYPE_2__ {scalar_t__ cache_size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct video_output {size_t available_frames; TYPE_1__ info; int /*<<< orphan*/ * cache; } ;
struct video_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_CACHE_SIZE ; 
 int /*<<< orphan*/  video_frame_init (struct video_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void init_cache(struct video_output *video)
{
	if (video->info.cache_size > MAX_CACHE_SIZE)
		video->info.cache_size = MAX_CACHE_SIZE;

	for (size_t i = 0; i < video->info.cache_size; i++) {
		struct video_frame *frame;
		frame = (struct video_frame *)&video->cache[i];

		video_frame_init(frame, video->info.format, video->info.width,
				 video->info.height);
	}

	video->available_frames = video->info.cache_size;
}