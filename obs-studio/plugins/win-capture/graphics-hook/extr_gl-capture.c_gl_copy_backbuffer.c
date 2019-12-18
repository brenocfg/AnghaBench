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
struct TYPE_2__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  base_cy; int /*<<< orphan*/  base_cx; int /*<<< orphan*/  fbo; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 scalar_t__ GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 scalar_t__ _strcmpi (int /*<<< orphan*/ ,char*) ; 
 int darkest_dungeon_fix ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlitFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFramebufferTexture2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  glReadBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ gl_error (char*,char*) ; 
 int /*<<< orphan*/  process_name ; 

__attribute__((used)) static void gl_copy_backbuffer(GLuint dst)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, data.fbo);
	if (gl_error("gl_copy_backbuffer", "failed to bind FBO")) {
		return;
	}

	glBindTexture(GL_TEXTURE_2D, dst);
	if (gl_error("gl_copy_backbuffer", "failed to bind texture")) {
		return;
	}

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			       GL_TEXTURE_2D, dst, 0);
	if (gl_error("gl_copy_backbuffer", "failed to set frame buffer")) {
		return;
	}

	glReadBuffer(GL_BACK);

	/* darkest dungeon fix */
	darkest_dungeon_fix = glGetError() == GL_INVALID_OPERATION &&
			      _strcmpi(process_name, "Darkest.exe") == 0;

	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	if (gl_error("gl_copy_backbuffer", "failed to set draw buffer")) {
		return;
	}

	glBlitFramebuffer(0, 0, data.base_cx, data.base_cy, 0, 0, data.cx,
			  data.cy, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	gl_error("gl_copy_backbuffer", "failed to blit");
}