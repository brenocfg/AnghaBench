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
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_texture {int /*<<< orphan*/  gl_target; int /*<<< orphan*/  texture; } ;
struct fbo_info {int /*<<< orphan*/  fbo; } ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 scalar_t__ GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER_BINDING ; 
 struct fbo_info* get_fbo (struct gs_texture*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCopyTexSubImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFramebufferTexture2D (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glReadBuffer (scalar_t__) ; 
 int /*<<< orphan*/  gl_bind_framebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_get_integer_v (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static bool gl_copy_fbo(struct gs_texture *dst, uint32_t dst_x, uint32_t dst_y,
			struct gs_texture *src, uint32_t src_x, uint32_t src_y,
			uint32_t width, uint32_t height)
{
	struct fbo_info *fbo = get_fbo(src, width, height);
	GLint last_fbo;
	bool success = false;

	if (!fbo)
		return false;

	if (!gl_get_integer_v(GL_READ_FRAMEBUFFER_BINDING, &last_fbo))
		return false;
	if (!gl_bind_framebuffer(GL_READ_FRAMEBUFFER, fbo->fbo))
		return false;
	if (!gl_bind_texture(dst->gl_target, dst->texture))
		goto fail;

	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0,
			       src->gl_target, src->texture, 0);
	if (!gl_success("glFrameBufferTexture2D"))
		goto fail;

	glReadBuffer(GL_COLOR_ATTACHMENT0 + 0);
	if (!gl_success("glReadBuffer"))
		goto fail;

	glCopyTexSubImage2D(dst->gl_target, 0, dst_x, dst_y, src_x, src_y,
			    width, height);
	if (!gl_success("glCopyTexSubImage2D"))
		goto fail;

	success = true;

fail:
	if (!gl_bind_texture(dst->gl_target, 0))
		success = false;
	if (!gl_bind_framebuffer(GL_READ_FRAMEBUFFER, last_fbo))
		success = false;

	return success;
}