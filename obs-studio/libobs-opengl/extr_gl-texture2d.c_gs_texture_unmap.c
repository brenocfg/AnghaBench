#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  texture; } ;
struct gs_texture_2d {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ base; int /*<<< orphan*/  unpack_buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  gl_type; int /*<<< orphan*/  gl_format; int /*<<< orphan*/  gl_internal_format; } ;
typedef  TYPE_2__ gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUnmapBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 
 int /*<<< orphan*/  is_texture_2d (TYPE_2__*,char*) ; 

void gs_texture_unmap(gs_texture_t *tex)
{
	struct gs_texture_2d *tex2d = (struct gs_texture_2d *)tex;
	if (!is_texture_2d(tex, "gs_texture_unmap"))
		goto failed;

	if (!gl_bind_buffer(GL_PIXEL_UNPACK_BUFFER, tex2d->unpack_buffer))
		goto failed;

	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	if (!gl_success("glUnmapBuffer"))
		goto failed;

	if (!gl_bind_texture(GL_TEXTURE_2D, tex2d->base.texture))
		goto failed;

	glTexImage2D(GL_TEXTURE_2D, 0, tex->gl_internal_format, tex2d->width,
		     tex2d->height, 0, tex->gl_format, tex->gl_type, 0);
	if (!gl_success("glTexImage2D"))
		goto failed;

	gl_bind_buffer(GL_PIXEL_UNPACK_BUFFER, 0);
	gl_bind_texture(GL_TEXTURE_2D, 0);
	return;

failed:
	gl_bind_buffer(GL_PIXEL_UNPACK_BUFFER, 0);
	gl_bind_texture(GL_TEXTURE_2D, 0);
	blog(LOG_ERROR, "gs_texture_unmap (GL) failed");
}