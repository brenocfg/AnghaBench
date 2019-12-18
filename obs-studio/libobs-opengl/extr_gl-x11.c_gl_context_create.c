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
struct gl_platform {int /*<<< orphan*/  pbuffer; int /*<<< orphan*/ * display; scalar_t__ context; } ;
typedef  int /*<<< orphan*/  GLXFBConfig ;
typedef  scalar_t__ GLXContext ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLAD_GLX_ARB_create_context ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ctx_attribs ; 
 int /*<<< orphan*/  ctx_pbuffer_attribs ; 
 int /*<<< orphan*/  ctx_visual_attribs ; 
 int /*<<< orphan*/ * glXChooseFBConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ glXCreateContextAttribsARB (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXCreatePbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gl_context_create(struct gl_platform *plat)
{
	Display *display = plat->display;
	int frame_buf_config_count = 0;
	GLXFBConfig *config = NULL;
	GLXContext context;
	bool success = false;

	if (!GLAD_GLX_ARB_create_context) {
		blog(LOG_ERROR, "ARB_GLX_create_context not supported!");
		return false;
	}

	config = glXChooseFBConfig(display, DefaultScreen(display),
				   ctx_visual_attribs, &frame_buf_config_count);
	if (!config) {
		blog(LOG_ERROR, "Failed to create OpenGL frame buffer config");
		return false;
	}

	context = glXCreateContextAttribsARB(display, config[0], NULL, true,
					     ctx_attribs);
	if (!context) {
		blog(LOG_ERROR, "Failed to create OpenGL context.");
		goto error;
	}

	plat->context = context;
	plat->display = display;

	plat->pbuffer =
		glXCreatePbuffer(display, config[0], ctx_pbuffer_attribs);
	if (!plat->pbuffer) {
		blog(LOG_ERROR, "Failed to create OpenGL pbuffer");
		goto error;
	}

	success = true;

error:
	XFree(config);
	XSync(display, false);
	return success;
}