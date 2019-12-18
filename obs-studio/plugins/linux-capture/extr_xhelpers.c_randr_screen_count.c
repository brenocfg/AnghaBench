#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ xcb_screen_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_screen_resources_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_screen_resources_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_4__ {TYPE_1__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_get_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_screen_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xcb_randr_get_screen_resources_crtcs_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_randr_get_screen_resources_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ xcb_setup_roots_iterator (int /*<<< orphan*/ ) ; 

int randr_screen_count(xcb_connection_t *xcb)
{
	if (!xcb)
		return 0;
	xcb_screen_t *screen;
	screen = xcb_setup_roots_iterator(xcb_get_setup(xcb)).data;

	xcb_randr_get_screen_resources_cookie_t res_c;
	xcb_randr_get_screen_resources_reply_t *res_r;

	res_c = xcb_randr_get_screen_resources(xcb, screen->root);
	res_r = xcb_randr_get_screen_resources_reply(xcb, res_c, 0);
	if (!res_r)
		return 0;

	return xcb_randr_get_screen_resources_crtcs_length(res_r);
}