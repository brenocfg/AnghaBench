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
typedef  int /*<<< orphan*/  xcb_get_geometry_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_geometry_cookie_t ;
typedef  int /*<<< orphan*/  xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_drawable_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_get_geometry_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static xcb_get_geometry_reply_t *get_window_geometry(xcb_connection_t *xcb_conn,
						     xcb_drawable_t drawable)
{
	xcb_get_geometry_cookie_t cookie;
	xcb_generic_error_t *error;
	xcb_get_geometry_reply_t *reply;

	cookie = xcb_get_geometry(xcb_conn, drawable);
	reply = xcb_get_geometry_reply(xcb_conn, cookie, &error);

	if (error) {
		blog(LOG_ERROR, "Failed to fetch parent window geometry!");
		free(error);
		free(reply);
		return 0;
	}

	free(error);
	return reply;
}