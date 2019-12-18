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
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_screen_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_screen_from_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_screen_num_from_xcb_screen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_screen_num_from_root(xcb_connection_t *xcb_conn,
					   xcb_window_t root)
{
	xcb_screen_t *screen = get_screen_from_root(xcb_conn, root);

	if (!screen)
		return -1;

	return get_screen_num_from_xcb_screen(xcb_conn, screen);
}