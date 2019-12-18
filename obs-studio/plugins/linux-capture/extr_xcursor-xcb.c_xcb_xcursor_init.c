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
typedef  int /*<<< orphan*/  xcb_xfixes_query_version_cookie_t ;
typedef  int /*<<< orphan*/  xcb_xcursor_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_XFIXES_MAJOR_VERSION ; 
 int /*<<< orphan*/  XCB_XFIXES_MINOR_VERSION ; 
 int /*<<< orphan*/ * bzalloc (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xfixes_query_version_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xfixes_query_version_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

xcb_xcursor_t *xcb_xcursor_init(xcb_connection_t *xcb)
{
	xcb_xcursor_t *data = bzalloc(sizeof(xcb_xcursor_t));

	xcb_xfixes_query_version_cookie_t xfix_c;

	xfix_c = xcb_xfixes_query_version_unchecked(
		xcb, XCB_XFIXES_MAJOR_VERSION, XCB_XFIXES_MINOR_VERSION);
	free(xcb_xfixes_query_version_reply(xcb, xfix_c, NULL));

	return data;
}