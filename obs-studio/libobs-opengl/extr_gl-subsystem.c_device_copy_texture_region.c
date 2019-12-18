#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct gs_texture_2d {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ format; } ;
typedef  TYPE_1__ gs_texture_t ;
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 scalar_t__ GS_TEXTURE_2D ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_copy_texture (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,scalar_t__,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void device_copy_texture_region(gs_device_t *device, gs_texture_t *dst,
				uint32_t dst_x, uint32_t dst_y,
				gs_texture_t *src, uint32_t src_x,
				uint32_t src_y, uint32_t src_w, uint32_t src_h)
{
	struct gs_texture_2d *src2d = (struct gs_texture_2d *)src;
	struct gs_texture_2d *dst2d = (struct gs_texture_2d *)dst;

	if (!src) {
		blog(LOG_ERROR, "Source texture is NULL");
		goto fail;
	}

	if (!dst) {
		blog(LOG_ERROR, "Destination texture is NULL");
		goto fail;
	}

	if (dst->type != GS_TEXTURE_2D || src->type != GS_TEXTURE_2D) {
		blog(LOG_ERROR, "Source and destination textures must be 2D "
				"textures");
		goto fail;
	}

	if (dst->format != src->format) {
		blog(LOG_ERROR, "Source and destination formats do not match");
		goto fail;
	}

	uint32_t nw = (uint32_t)src_w ? (uint32_t)src_w
				      : (src2d->width - src_x);
	uint32_t nh = (uint32_t)src_h ? (uint32_t)src_h
				      : (src2d->height - src_y);

	if (dst2d->width - dst_x < nw || dst2d->height - dst_y < nh) {
		blog(LOG_ERROR, "Destination texture region is not big "
				"enough to hold the source region");
		goto fail;
	}

	if (!gl_copy_texture(device, dst, dst_x, dst_y, src, src_x, src_y, nw,
			     nh))
		goto fail;

	return;

fail:
	blog(LOG_ERROR, "device_copy_texture (GL) failed");
}