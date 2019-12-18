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
struct xshm_data {char* server; int use_randr; int use_xinerama; int /*<<< orphan*/  y_org; int /*<<< orphan*/  x_org; int /*<<< orphan*/  cursor; int /*<<< orphan*/  xcb; int /*<<< orphan*/  xshm; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ advanced; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 scalar_t__ randr_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_connect (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_connection_has_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xcursor_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xcursor_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xinerama_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xshm_capture_stop (struct xshm_data*) ; 
 int /*<<< orphan*/  xshm_check_extensions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xshm_resize_texture (struct xshm_data*) ; 
 scalar_t__ xshm_update_geometry (struct xshm_data*) ; 
 int /*<<< orphan*/  xshm_xcb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xshm_capture_start(struct xshm_data *data)
{
	const char *server = (data->advanced && *data->server) ? data->server
							       : NULL;

	data->xcb = xcb_connect(server, NULL);
	if (!data->xcb || xcb_connection_has_error(data->xcb)) {
		blog(LOG_ERROR, "Unable to open X display !");
		goto fail;
	}

	if (!xshm_check_extensions(data->xcb))
		goto fail;

	data->use_randr = randr_is_active(data->xcb) ? true : false;
	data->use_xinerama = xinerama_is_active(data->xcb) ? true : false;

	if (xshm_update_geometry(data) < 0) {
		blog(LOG_ERROR, "failed to update geometry !");
		goto fail;
	}

	data->xshm = xshm_xcb_attach(data->xcb, data->width, data->height);
	if (!data->xshm) {
		blog(LOG_ERROR, "failed to attach shm !");
		goto fail;
	}

	data->cursor = xcb_xcursor_init(data->xcb);
	xcb_xcursor_offset(data->cursor, data->x_org, data->y_org);

	obs_enter_graphics();

	xshm_resize_texture(data);

	obs_leave_graphics();

	return;
fail:
	xshm_capture_stop(data);
}