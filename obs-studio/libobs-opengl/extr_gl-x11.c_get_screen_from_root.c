#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_window_t ;
struct TYPE_6__ {scalar_t__ root; } ;
typedef  TYPE_1__ xcb_screen_t ;
struct TYPE_7__ {TYPE_1__* data; scalar_t__ rem; } ;
typedef  TYPE_2__ xcb_screen_iterator_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_get_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_screen_next (TYPE_2__*) ; 
 TYPE_2__ xcb_setup_roots_iterator (int /*<<< orphan*/ ) ; 

__attribute__((used)) static xcb_screen_t *get_screen_from_root(xcb_connection_t *xcb_conn,
					  xcb_window_t root)
{
	xcb_screen_iterator_t iter =
		xcb_setup_roots_iterator(xcb_get_setup(xcb_conn));

	while (iter.rem) {
		if (iter.data->root == root)
			return iter.data;

		xcb_screen_next(&iter);
	}

	return 0;
}