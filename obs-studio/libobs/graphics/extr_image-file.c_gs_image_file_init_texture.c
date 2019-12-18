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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  frame_image; } ;
struct TYPE_5__ {int /*<<< orphan*/ * texture_data; int /*<<< orphan*/  format; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; void* texture; TYPE_1__ gif; scalar_t__ is_animated_gif; int /*<<< orphan*/  loaded; } ;
typedef  TYPE_2__ gs_image_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DYNAMIC ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 void* gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

void gs_image_file_init_texture(gs_image_file_t *image)
{
	if (!image->loaded)
		return;

	if (image->is_animated_gif) {
		image->texture = gs_texture_create(
			image->cx, image->cy, image->format, 1,
			(const uint8_t **)&image->gif.frame_image, GS_DYNAMIC);

	} else {
		image->texture = gs_texture_create(
			image->cx, image->cy, image->format, 1,
			(const uint8_t **)&image->texture_data, 0);
		bfree(image->texture_data);
		image->texture_data = NULL;
	}
}