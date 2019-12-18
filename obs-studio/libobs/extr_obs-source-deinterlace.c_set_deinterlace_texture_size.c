#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int async_channel_count; int* async_texture_formats; int /*<<< orphan*/  async_height; int /*<<< orphan*/  async_width; void** async_prev_textures; int /*<<< orphan*/  async_format; int /*<<< orphan*/ * async_convert_height; int /*<<< orphan*/ * async_convert_width; int /*<<< orphan*/  async_prev_texrender; scalar_t__ async_gpu_conversion; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BGRX ; 
 int /*<<< orphan*/  GS_DYNAMIC ; 
 int /*<<< orphan*/  GS_ZS_NONE ; 
 int convert_video_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texrender_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void set_deinterlace_texture_size(obs_source_t *source)
{
	if (source->async_gpu_conversion) {
		source->async_prev_texrender =
			gs_texrender_create(GS_BGRX, GS_ZS_NONE);

		for (int c = 0; c < source->async_channel_count; c++)
			source->async_prev_textures[c] = gs_texture_create(
				source->async_convert_width[c],
				source->async_convert_height[c],
				source->async_texture_formats[c], 1, NULL,
				GS_DYNAMIC);

	} else {
		enum gs_color_format format =
			convert_video_format(source->async_format);

		source->async_prev_textures[0] = gs_texture_create(
			source->async_width, source->async_height, format, 1,
			NULL, GS_DYNAMIC);
	}
}