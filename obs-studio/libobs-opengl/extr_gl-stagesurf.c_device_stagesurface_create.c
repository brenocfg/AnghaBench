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
typedef  void* uint32_t ;
struct gs_stage_surface {int format; int bytes_per_pixel; int /*<<< orphan*/  gl_type; int /*<<< orphan*/  gl_internal_format; int /*<<< orphan*/  gl_format; void* height; void* width; int /*<<< orphan*/ * device; } ;
typedef  struct gs_stage_surface gs_stagesurf_t ;
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct gs_stage_surface* bzalloc (int) ; 
 int /*<<< orphan*/  convert_gs_format (int) ; 
 int /*<<< orphan*/  convert_gs_internal_format (int) ; 
 int /*<<< orphan*/  create_pixel_pack_buffer (struct gs_stage_surface*) ; 
 int /*<<< orphan*/  get_gl_format_type (int) ; 
 int gs_get_format_bpp (int) ; 
 int /*<<< orphan*/  gs_stagesurface_destroy (struct gs_stage_surface*) ; 

gs_stagesurf_t *device_stagesurface_create(gs_device_t *device, uint32_t width,
					   uint32_t height,
					   enum gs_color_format color_format)
{
	struct gs_stage_surface *surf;
	surf = bzalloc(sizeof(struct gs_stage_surface));
	surf->device = device;
	surf->format = color_format;
	surf->width = width;
	surf->height = height;
	surf->gl_format = convert_gs_format(color_format);
	surf->gl_internal_format = convert_gs_internal_format(color_format);
	surf->gl_type = get_gl_format_type(color_format);
	surf->bytes_per_pixel = gs_get_format_bpp(color_format) / 8;

	if (!create_pixel_pack_buffer(surf)) {
		blog(LOG_ERROR, "device_stagesurface_create (GL) failed");
		gs_stagesurface_destroy(surf);
		return NULL;
	}

	return surf;
}