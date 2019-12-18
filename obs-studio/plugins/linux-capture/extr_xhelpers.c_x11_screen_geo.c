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
typedef  TYPE_2__ xcb_screen_iterator_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  int_fast32_t ;
struct TYPE_5__ {int /*<<< orphan*/  height_in_pixels; int /*<<< orphan*/  width_in_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_get_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_screen_next (TYPE_2__*) ; 
 TYPE_2__ xcb_setup_roots_iterator (int /*<<< orphan*/ ) ; 

int x11_screen_geo(xcb_connection_t *xcb, int_fast32_t screen, int_fast32_t *w,
		   int_fast32_t *h)
{
	if (!xcb)
		goto fail;

	bool success = false;
	xcb_screen_iterator_t iter;

	iter = xcb_setup_roots_iterator(xcb_get_setup(xcb));
	for (; iter.rem; --screen, xcb_screen_next(&iter)) {
		if (!screen) {
			*w = iter.data->width_in_pixels;
			*h = iter.data->height_in_pixels;
			success = true;
		}
	}

	if (success)
		return 0;

fail:
	*w = *h = 0;
	return -1;
}