#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {unsigned int frame_count; } ;
struct TYPE_6__ {int cur_frame; scalar_t__ cur_time; int cur_loop; TYPE_1__ gif; } ;
typedef  TYPE_2__ gs_image_file_t ;

/* Variables and functions */
 scalar_t__ get_time (TYPE_2__*,int) ; 

__attribute__((used)) static inline int calculate_new_frame(gs_image_file_t *image,
				      uint64_t elapsed_time_ns, int loops)
{
	int new_frame = image->cur_frame;

	image->cur_time += elapsed_time_ns;
	for (;;) {
		uint64_t t = get_time(image, new_frame);
		if (image->cur_time <= t)
			break;

		image->cur_time -= t;
		if ((unsigned int)++new_frame == image->gif.frame_count) {
			if (!loops || ++image->cur_loop < loops) {
				new_frame = 0;
			} else if (image->cur_loop == loops) {
				new_frame--;
				break;
			}
		}
	}

	return new_frame;
}