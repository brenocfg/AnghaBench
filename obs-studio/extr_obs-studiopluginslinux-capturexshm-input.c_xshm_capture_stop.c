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
struct xshm_data {int /*<<< orphan*/ * server; int /*<<< orphan*/ * xcb; int /*<<< orphan*/ * xshm; int /*<<< orphan*/ * cursor; int /*<<< orphan*/ * texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xcursor_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xshm_xcb_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xshm_capture_stop(struct xshm_data *data)
{
	obs_enter_graphics();

	if (data->texture) {
		gs_texture_destroy(data->texture);
		data->texture = NULL;
	}
	if (data->cursor) {
		xcb_xcursor_destroy(data->cursor);
		data->cursor = NULL;
	}

	obs_leave_graphics();

	if (data->xshm) {
		xshm_xcb_detach(data->xshm);
		data->xshm = NULL;
	}

	if (data->xcb) {
		xcb_disconnect(data->xcb);
		data->xcb = NULL;
	}

	if (data->server) {
		bfree(data->server);
		data->server = NULL;
	}
}