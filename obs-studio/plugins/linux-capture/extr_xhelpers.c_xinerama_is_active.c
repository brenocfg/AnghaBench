#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ xcb_xinerama_is_active_reply_t ;
typedef  int /*<<< orphan*/  xcb_xinerama_is_active_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_6__ {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_3__* xcb_get_extension_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_id ; 
 TYPE_1__* xcb_xinerama_is_active_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_is_active_unchecked (int /*<<< orphan*/ *) ; 

bool xinerama_is_active(xcb_connection_t *xcb)
{
	if (!xcb || !xcb_get_extension_data(xcb, &xcb_xinerama_id)->present)
		return false;

	bool active = true;
	xcb_xinerama_is_active_cookie_t xnr_c;
	xcb_xinerama_is_active_reply_t *xnr_r;

	xnr_c = xcb_xinerama_is_active_unchecked(xcb);
	xnr_r = xcb_xinerama_is_active_reply(xcb, xnr_c, NULL);
	if (!xnr_r || xnr_r->state == 0)
		active = false;
	free(xnr_r);

	return active;
}