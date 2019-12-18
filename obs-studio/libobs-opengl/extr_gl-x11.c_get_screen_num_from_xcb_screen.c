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
typedef  int /*<<< orphan*/  xcb_screen_t ;
struct TYPE_4__ {int /*<<< orphan*/ * data; scalar_t__ rem; } ;
typedef  TYPE_1__ xcb_screen_iterator_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_get_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_screen_next (TYPE_1__*) ; 
 TYPE_1__ xcb_setup_roots_iterator (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_screen_num_from_xcb_screen(xcb_connection_t *xcb_conn,
					  xcb_screen_t *screen)
{
	xcb_screen_iterator_t iter =
		xcb_setup_roots_iterator(xcb_get_setup(xcb_conn));
	int screen_num = 0;

	for (; iter.rem; xcb_screen_next(&iter), ++screen_num)
		if (iter.data == screen)
			return screen_num;

	return -1;
}