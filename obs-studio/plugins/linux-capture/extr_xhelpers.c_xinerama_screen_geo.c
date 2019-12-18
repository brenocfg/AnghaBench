#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* data; scalar_t__ rem; } ;
typedef  TYPE_2__ xcb_xinerama_screen_info_iterator_t ;
typedef  int /*<<< orphan*/  xcb_xinerama_query_screens_reply_t ;
typedef  int /*<<< orphan*/  xcb_xinerama_query_screens_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  int_fast32_t ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_org; int /*<<< orphan*/  x_org; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_xinerama_query_screens_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ xcb_xinerama_query_screens_screen_info_iterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_query_screens_unchecked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_screen_info_next (TYPE_2__*) ; 

int xinerama_screen_geo(xcb_connection_t *xcb, int_fast32_t screen,
			int_fast32_t *x, int_fast32_t *y, int_fast32_t *w,
			int_fast32_t *h)
{
	if (!xcb)
		goto fail;

	bool success = false;
	xcb_xinerama_query_screens_cookie_t scr_c;
	xcb_xinerama_query_screens_reply_t *scr_r;
	xcb_xinerama_screen_info_iterator_t iter;

	scr_c = xcb_xinerama_query_screens_unchecked(xcb);
	scr_r = xcb_xinerama_query_screens_reply(xcb, scr_c, NULL);
	if (!scr_r)
		goto fail;

	iter = xcb_xinerama_query_screens_screen_info_iterator(scr_r);
	for (; iter.rem; --screen, xcb_xinerama_screen_info_next(&iter)) {
		if (!screen) {
			*x = iter.data->x_org;
			*y = iter.data->y_org;
			*w = iter.data->width;
			*h = iter.data->height;
			success = true;
		}
	}
	free(scr_r);

	if (success)
		return 0;

fail:
	*x = *y = *w = *h = 0;
	return -1;
}