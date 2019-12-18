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
struct TYPE_2__ {int /*<<< orphan*/  format; } ;
struct gs_texture_2d {int width; int height; TYPE_1__ base; int /*<<< orphan*/  unpack_buffer; } ;
typedef  int GLsizeiptr ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DYNAMIC_DRAW ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_gen_buffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_success (char*) ; 
 int gs_get_format_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_is_compressed_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool create_pixel_unpack_buffer(struct gs_texture_2d *tex)
{
	GLsizeiptr size;
	bool success = true;

	if (!gl_gen_buffers(1, &tex->unpack_buffer))
		return false;

	if (!gl_bind_buffer(GL_PIXEL_UNPACK_BUFFER, tex->unpack_buffer))
		return false;

	size = tex->width * gs_get_format_bpp(tex->base.format);
	if (!gs_is_compressed_format(tex->base.format)) {
		size /= 8;
		size = (size + 3) & 0xFFFFFFFC;
		size *= tex->height;
	} else {
		size *= tex->height;
		size /= 8;
	}

	glBufferData(GL_PIXEL_UNPACK_BUFFER, size, 0, GL_DYNAMIC_DRAW);
	if (!gl_success("glBufferData"))
		success = false;

	if (!gl_bind_buffer(GL_PIXEL_UNPACK_BUFFER, 0))
		success = false;

	return success;
}