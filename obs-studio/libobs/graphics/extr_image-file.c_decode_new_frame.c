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
struct TYPE_5__ {int width; int height; int /*<<< orphan*/  frame_image; } ;
struct TYPE_4__ {int last_decoded_frame; int cur_frame; TYPE_2__ gif; scalar_t__* animation_frame_cache; scalar_t__ animation_frame_data; } ;
typedef  TYPE_1__ gs_image_file_t ;

/* Variables and functions */
 scalar_t__ GIF_OK ; 
 scalar_t__ gif_decode_frame (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void decode_new_frame(gs_image_file_t *image, int new_frame)
{
	if (!image->animation_frame_cache[new_frame]) {
		int last_frame;

		/* if looped, decode frame 0 */
		last_frame = (new_frame < image->last_decoded_frame)
				     ? 0
				     : image->last_decoded_frame + 1;

		/* decode missed frames */
		for (int i = last_frame; i < new_frame; i++) {
			if (gif_decode_frame(&image->gif, i) != GIF_OK)
				return;
		}

		/* decode actual desired frame */
		if (gif_decode_frame(&image->gif, new_frame) == GIF_OK) {
			size_t pos = new_frame * image->gif.width *
				     image->gif.height * 4;
			image->animation_frame_cache[new_frame] =
				image->animation_frame_data + pos;

			memcpy(image->animation_frame_cache[new_frame],
			       image->gif.frame_image,
			       image->gif.width * image->gif.height * 4);

			image->last_decoded_frame = new_frame;
		}
	}

	image->cur_frame = new_frame;
}