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
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_texture_cube {int /*<<< orphan*/  size; } ;
struct gs_texture_2d {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ gs_texture_t ;

/* Variables and functions */
 scalar_t__ GS_TEXTURE_2D ; 
 scalar_t__ GS_TEXTURE_CUBE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool get_tex_dimensions(gs_texture_t *tex, uint32_t *width,
			       uint32_t *height)
{
	if (tex->type == GS_TEXTURE_2D) {
		struct gs_texture_2d *tex2d = (struct gs_texture_2d *)tex;
		*width = tex2d->width;
		*height = tex2d->height;
		return true;

	} else if (tex->type == GS_TEXTURE_CUBE) {
		struct gs_texture_cube *cube = (struct gs_texture_cube *)tex;
		*width = cube->size;
		*height = cube->size;
		return true;
	}

	blog(LOG_ERROR, "Texture must be 2D or cubemap");
	return false;
}