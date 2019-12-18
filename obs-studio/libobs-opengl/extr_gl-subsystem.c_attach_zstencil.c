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
struct fbo_info {TYPE_1__* cur_zstencil_buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  attachment; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ gs_zstencil_t ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  glFramebufferRenderbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static bool attach_zstencil(struct fbo_info *fbo, gs_zstencil_t *zs)
{
	GLuint zsbuffer = 0;
	GLenum zs_attachment = GL_DEPTH_STENCIL_ATTACHMENT;

	if (fbo->cur_zstencil_buffer == zs)
		return true;

	fbo->cur_zstencil_buffer = zs;

	if (zs) {
		zsbuffer = zs->buffer;
		zs_attachment = zs->attachment;
	}

	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, zs_attachment,
				  GL_RENDERBUFFER, zsbuffer);
	if (!gl_success("glFramebufferRenderbuffer"))
		return false;

	return true;
}