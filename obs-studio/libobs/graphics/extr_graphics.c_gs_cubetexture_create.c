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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* device_cubetexture_create ) (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/  const**,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int GS_BUILD_MIPMAPS ; 
 int GS_RENDER_TARGET ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int is_pow2 (int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/  const**,int) ; 
 TYPE_2__* thread_graphics ; 

gs_texture_t *gs_cubetexture_create(uint32_t size,
				    enum gs_color_format color_format,
				    uint32_t levels, const uint8_t **data,
				    uint32_t flags)
{
	graphics_t *graphics = thread_graphics;
	bool pow2tex = is_pow2(size);
	bool uses_mipmaps = (flags & GS_BUILD_MIPMAPS || levels != 1);

	if (!gs_valid("gs_cubetexture_create"))
		return NULL;

	if (uses_mipmaps && !pow2tex) {
		blog(LOG_WARNING, "Cannot use mipmaps with a "
				  "non-power-of-two texture.  Disabling "
				  "mipmaps for this texture.");

		uses_mipmaps = false;
		flags &= ~GS_BUILD_MIPMAPS;
		levels = 1;
	}

	if (uses_mipmaps && flags & GS_RENDER_TARGET) {
		blog(LOG_WARNING, "Cannot use mipmaps with render targets.  "
				  "Disabling mipmaps for this texture.");
		flags &= ~GS_BUILD_MIPMAPS;
		levels = 1;
		data = NULL;
	}

	return graphics->exports.device_cubetexture_create(
		graphics->device, size, color_format, levels, data, flags);
}