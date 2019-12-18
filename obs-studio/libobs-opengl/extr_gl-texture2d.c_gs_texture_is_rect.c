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
struct TYPE_2__ {scalar_t__ gl_target; } ;
struct gs_texture_2d {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE_RECTANGLE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_texture_2d (int /*<<< orphan*/  const*,char*) ; 

bool gs_texture_is_rect(const gs_texture_t *tex)
{
	const struct gs_texture_2d *tex2d = (const struct gs_texture_2d *)tex;
	if (!is_texture_2d(tex, "gs_texture_unmap")) {
		blog(LOG_ERROR, "gs_texture_is_rect (GL) failed");
		return false;
	}

	return tex2d->base.gl_target == GL_TEXTURE_RECTANGLE;
}