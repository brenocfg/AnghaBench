#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ last_serial; scalar_t__ y_org; scalar_t__ render_y; scalar_t__ x_org; scalar_t__ render_x; void* y; void* x; int /*<<< orphan*/  tex; int /*<<< orphan*/  dpy; } ;
typedef  TYPE_1__ xcursor_t ;
typedef  void* int_fast32_t ;
struct TYPE_9__ {scalar_t__ cursor_serial; scalar_t__ yhot; scalar_t__ y; scalar_t__ xhot; scalar_t__ x; } ;
typedef  TYPE_2__ XFixesCursorImage ;

/* Variables and functions */
 TYPE_2__* XFixesGetCursorImage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 int /*<<< orphan*/  xcursor_create (TYPE_1__*,TYPE_2__*) ; 

void xcursor_tick(xcursor_t *data)
{
	XFixesCursorImage *xc = XFixesGetCursorImage(data->dpy);
	if (!xc)
		return;

	if (!data->tex || data->last_serial != xc->cursor_serial)
		xcursor_create(data, xc);

	data->x = (int_fast32_t)xc->x - (int_fast32_t)data->x_org;
	data->y = (int_fast32_t)xc->y - (int_fast32_t)data->y_org;
	data->render_x = xc->x - xc->xhot - data->x_org;
	data->render_y = xc->y - xc->yhot - data->y_org;

	XFree(xc);
}