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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int levels; int /*<<< orphan*/  gl_internal_format; int /*<<< orphan*/  gl_format; int /*<<< orphan*/  gl_type; int /*<<< orphan*/  texture; int /*<<< orphan*/  format; } ;
struct gs_texture_2d {int width; int height; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_LEVEL ; 
 int /*<<< orphan*/  gl_bind_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gl_init_face (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/  const***) ; 
 int /*<<< orphan*/  gl_tex_param_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gs_get_format_bpp (int /*<<< orphan*/ ) ; 
 int gs_get_total_levels (int,int) ; 
 int gs_is_compressed_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool upload_texture_2d(struct gs_texture_2d *tex, const uint8_t **data)
{
	uint32_t row_size = tex->width * gs_get_format_bpp(tex->base.format);
	uint32_t tex_size = tex->height * row_size / 8;
	uint32_t num_levels = tex->base.levels;
	bool compressed = gs_is_compressed_format(tex->base.format);
	bool success;

	if (!num_levels)
		num_levels = gs_get_total_levels(tex->width, tex->height);

	if (!gl_bind_texture(GL_TEXTURE_2D, tex->base.texture))
		return false;

	success = gl_init_face(GL_TEXTURE_2D, tex->base.gl_type, num_levels,
			       tex->base.gl_format,
			       tex->base.gl_internal_format, compressed,
			       tex->width, tex->height, tex_size, &data);

	if (!gl_tex_param_i(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,
			    num_levels - 1))
		success = false;
	if (!gl_bind_texture(GL_TEXTURE_2D, 0))
		success = false;

	return success;
}