#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int number; } ;
typedef  TYPE_1__ xcb_xinerama_query_screens_reply_t ;
typedef  int /*<<< orphan*/  xcb_xinerama_query_screens_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* xcb_xinerama_query_screens_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_query_screens_unchecked (int /*<<< orphan*/ *) ; 

int xinerama_screen_count(xcb_connection_t *xcb)
{
	if (!xcb)
		return 0;

	int screens = 0;
	xcb_xinerama_query_screens_cookie_t scr_c;
	xcb_xinerama_query_screens_reply_t *scr_r;

	scr_c = xcb_xinerama_query_screens_unchecked(xcb);
	scr_r = xcb_xinerama_query_screens_reply(xcb, scr_c, NULL);
	if (scr_r)
		screens = scr_r->number;
	free(scr_r);

	return screens;
}