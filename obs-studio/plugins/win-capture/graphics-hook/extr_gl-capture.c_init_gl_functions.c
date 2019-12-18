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

/* Variables and functions */
 int /*<<< orphan*/  GET_PROC (int (*) (),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_get_proc (char*) ; 
 int /*<<< orphan*/  glBindBuffer ; 
 int /*<<< orphan*/  glBindFramebuffer ; 
 int /*<<< orphan*/  glBindTexture ; 
 int /*<<< orphan*/  glBlitFramebuffer ; 
 int /*<<< orphan*/  glBufferData ; 
 int /*<<< orphan*/  glDeleteBuffers ; 
 int /*<<< orphan*/  glDeleteFramebuffers ; 
 int /*<<< orphan*/  glDeleteTextures ; 
 int /*<<< orphan*/  glDrawBuffer ; 
 int /*<<< orphan*/  glFramebufferTexture2D ; 
 int /*<<< orphan*/  glGenBuffers ; 
 int /*<<< orphan*/  glGenFramebuffers ; 
 int /*<<< orphan*/  glGenTextures ; 
 int /*<<< orphan*/  glGetError ; 
 int /*<<< orphan*/  glGetIntegerv ; 
 int /*<<< orphan*/  glGetTexImage ; 
 int /*<<< orphan*/  glMapBuffer ; 
 int /*<<< orphan*/  glReadBuffer ; 
 int /*<<< orphan*/  glTexImage2D ; 
 int /*<<< orphan*/  glUnmapBuffer ; 
 int /*<<< orphan*/  hlog (char*) ; 
 int /*<<< orphan*/  init_nv_functions () ; 
 int /*<<< orphan*/  jimglGetCurrentContext ; 
 int /*<<< orphan*/  jimglGetCurrentDC ; 
 int /*<<< orphan*/  jimglGetProcAddress ; 
 int /*<<< orphan*/  jimglMakeCurrent ; 
 int /*<<< orphan*/  wglGetCurrentContext ; 
 int /*<<< orphan*/  wglGetCurrentDC ; 
 int /*<<< orphan*/  wglMakeCurrent ; 

__attribute__((used)) static bool init_gl_functions(void)
{
	bool success = true;

	jimglGetProcAddress = base_get_proc("wglGetProcAddress");
	if (!jimglGetProcAddress) {
		hlog("init_gl_functions: failed to get wglGetProcAddress");
		return false;
	}

	GET_PROC(init_gl_functions, jimglMakeCurrent, wglMakeCurrent);
	GET_PROC(init_gl_functions, jimglGetCurrentDC, wglGetCurrentDC);
	GET_PROC(init_gl_functions, jimglGetCurrentContext,
		 wglGetCurrentContext);
	GET_PROC(init_gl_functions, glTexImage2D, glTexImage2D);
	GET_PROC(init_gl_functions, glReadBuffer, glReadBuffer);
	GET_PROC(init_gl_functions, glGetTexImage, glGetTexImage);
	GET_PROC(init_gl_functions, glDrawBuffer, glDrawBuffer);
	GET_PROC(init_gl_functions, glGetError, glGetError);
	GET_PROC(init_gl_functions, glBufferData, glBufferData);
	GET_PROC(init_gl_functions, glDeleteBuffers, glDeleteBuffers);
	GET_PROC(init_gl_functions, glDeleteTextures, glDeleteTextures);
	GET_PROC(init_gl_functions, glGenBuffers, glGenBuffers);
	GET_PROC(init_gl_functions, glGenTextures, glGenTextures);
	GET_PROC(init_gl_functions, glMapBuffer, glMapBuffer);
	GET_PROC(init_gl_functions, glUnmapBuffer, glUnmapBuffer);
	GET_PROC(init_gl_functions, glBindBuffer, glBindBuffer);
	GET_PROC(init_gl_functions, glGetIntegerv, glGetIntegerv);
	GET_PROC(init_gl_functions, glBindTexture, glBindTexture);
	GET_PROC(init_gl_functions, glGenFramebuffers, glGenFramebuffers);
	GET_PROC(init_gl_functions, glDeleteFramebuffers, glDeleteFramebuffers);
	GET_PROC(init_gl_functions, glBindFramebuffer, glBindFramebuffer);
	GET_PROC(init_gl_functions, glBlitFramebuffer, glBlitFramebuffer);
	GET_PROC(init_gl_functions, glFramebufferTexture2D,
		 glFramebufferTexture2D);

	init_nv_functions();
	return success;
}