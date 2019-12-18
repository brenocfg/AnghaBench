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
struct TYPE_2__ {int levels; int /*<<< orphan*/  gl_internal_format; int /*<<< orphan*/  gl_format; int /*<<< orphan*/  texture; int /*<<< orphan*/  format; } ;
struct gs_texture_cube {int size; TYPE_1__ base; } ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP ; 
 scalar_t__ GL_TEXTURE_CUBE_MAP_POSITIVE_X ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_LEVEL ; 
 scalar_t__ get_gl_format_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_bind_texture (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_init_face (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/  const***) ; 
 int /*<<< orphan*/  gl_success (char*) ; 
 int gs_get_format_bpp (int /*<<< orphan*/ ) ; 
 int gs_get_total_levels (int,int) ; 
 int gs_is_compressed_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool upload_texture_cube(struct gs_texture_cube *tex,
				       const uint8_t **data)
{
	uint32_t row_size = tex->size * gs_get_format_bpp(tex->base.format);
	uint32_t tex_size = tex->size * row_size / 8;
	uint32_t num_levels = tex->base.levels;
	bool compressed = gs_is_compressed_format(tex->base.format);
	GLenum gl_type = get_gl_format_type(tex->base.format);
	bool success = true;
	uint32_t i;

	if (!num_levels)
		num_levels = gs_get_total_levels(tex->size, tex->size);

	for (i = 0; i < 6; i++) {
		GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;

		if (!gl_bind_texture(target, tex->base.texture))
			success = false;

		if (!gl_init_face(target, gl_type, num_levels,
				  tex->base.gl_format,
				  tex->base.gl_internal_format, compressed,
				  tex->size, tex->size, tex_size, &data))
			success = false;

		if (!gl_bind_texture(target, 0))
			success = false;

		if (data)
			data++;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, num_levels);
	if (!gl_success("glTexParameteri"))
		success = false;

	return success;
}