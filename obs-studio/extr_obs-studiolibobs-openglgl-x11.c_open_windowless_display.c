#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ xcb_screen_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ xcb_screen_iterator_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XGetXCBConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int get_screen_num_from_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gladLoadGLX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xcb_get_setup (int /*<<< orphan*/ *) ; 
 TYPE_2__ xcb_setup_roots_iterator (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Display *open_windowless_display(void)
{
	Display *display = XOpenDisplay(NULL);
	xcb_connection_t *xcb_conn;
	xcb_screen_iterator_t screen_iterator;
	xcb_screen_t *screen;
	int screen_num;

	if (!display) {
		blog(LOG_ERROR, "Unable to open new X connection!");
		return NULL;
	}

	xcb_conn = XGetXCBConnection(display);
	if (!xcb_conn) {
		blog(LOG_ERROR, "Unable to get XCB connection to main display");
		goto error;
	}

	screen_iterator = xcb_setup_roots_iterator(xcb_get_setup(xcb_conn));
	screen = screen_iterator.data;
	if (!screen) {
		blog(LOG_ERROR, "Unable to get screen root");
		goto error;
	}

	screen_num = get_screen_num_from_root(xcb_conn, screen->root);
	if (screen_num == -1) {
		blog(LOG_ERROR, "Unable to get screen number from root");
		goto error;
	}

	if (!gladLoadGLX(display, screen_num)) {
		blog(LOG_ERROR, "Unable to load GLX entry functions.");
		goto error;
	}

	return display;

error:
	if (display)
		XCloseDisplay(display);
	return NULL;
}