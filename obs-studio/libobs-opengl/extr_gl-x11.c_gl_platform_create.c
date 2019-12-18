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
typedef  int /*<<< orphan*/  uint32_t ;
struct gl_platform {int /*<<< orphan*/  context; int /*<<< orphan*/  pbuffer; int /*<<< orphan*/ * display; } ;
struct TYPE_3__ {struct gl_platform* plat; } ;
typedef  TYPE_1__ gs_device_t ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCBOwnsEventQueue ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSetErrorHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetEventQueueOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (struct gl_platform*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct gl_platform* bmalloc (int) ; 
 int /*<<< orphan*/  glXMakeContextCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_context_create (struct gl_platform*) ; 
 int /*<<< orphan*/  gl_context_destroy (struct gl_platform*) ; 
 int /*<<< orphan*/  gladLoadGL () ; 
 int /*<<< orphan*/ * open_windowless_display () ; 
 int /*<<< orphan*/  x_error_handler ; 

extern struct gl_platform *gl_platform_create(gs_device_t *device,
					      uint32_t adapter)
{
	/* There's some trickery here... we're mixing libX11, xcb, and GLX
	   For an explanation see here: http://xcb.freedesktop.org/MixingCalls/
	   Essentially, GLX requires Xlib. Everything else we use xcb. */
	struct gl_platform *plat = bmalloc(sizeof(struct gl_platform));
	Display *display = open_windowless_display();

	if (!display) {
		goto fail_display_open;
	}

	XSetEventQueueOwner(display, XCBOwnsEventQueue);
	XSetErrorHandler(x_error_handler);

	/* We assume later that cur_swap is already set. */
	device->plat = plat;

	plat->display = display;

	if (!gl_context_create(plat)) {
		blog(LOG_ERROR, "Failed to create context!");
		goto fail_context_create;
	}

	if (!glXMakeContextCurrent(plat->display, plat->pbuffer, plat->pbuffer,
				   plat->context)) {
		blog(LOG_ERROR, "Failed to make context current.");
		goto fail_make_current;
	}

	if (!gladLoadGL()) {
		blog(LOG_ERROR, "Failed to load OpenGL entry functions.");
		goto fail_load_gl;
	}

	goto success;

fail_make_current:
	gl_context_destroy(plat);
fail_context_create:
fail_load_gl:
	XCloseDisplay(display);
fail_display_open:
	bfree(plat);
	plat = NULL;
success:
	UNUSED_PARAMETER(adapter);
	return plat;
}