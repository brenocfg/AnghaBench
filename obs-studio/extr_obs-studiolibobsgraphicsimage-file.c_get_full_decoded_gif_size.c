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
struct TYPE_4__ {int width; int height; int frame_count; } ;
struct TYPE_5__ {TYPE_1__ gif; } ;
typedef  TYPE_2__ gs_image_file_t ;

/* Variables and functions */

__attribute__((used)) static inline int get_full_decoded_gif_size(gs_image_file_t *image)
{
	return image->gif.width * image->gif.height * 4 * image->gif.frame_count;
}