#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ xcb_get_geometry_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_swap_chain {TYPE_3__* wi; TYPE_2__* device; } ;
struct TYPE_9__ {int /*<<< orphan*/  window; } ;
struct TYPE_8__ {TYPE_1__* plat; } ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/ * XGetXCBConnection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* get_window_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

extern void gl_getclientsize(const struct gs_swap_chain *swap, uint32_t *width,
			     uint32_t *height)
{
	xcb_connection_t *xcb_conn =
		XGetXCBConnection(swap->device->plat->display);
	xcb_window_t window = swap->wi->window;

	xcb_get_geometry_reply_t *geometry =
		get_window_geometry(xcb_conn, window);
	if (geometry) {
		*width = geometry->width;
		*height = geometry->height;
	}

	free(geometry);
}