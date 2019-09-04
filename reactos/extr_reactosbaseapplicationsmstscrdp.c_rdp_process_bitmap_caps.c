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
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 scalar_t__ g_height ; 
 scalar_t__ g_server_depth ; 
 scalar_t__ g_width ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_resize_window () ; 
 int /*<<< orphan*/  warning (char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static void
rdp_process_bitmap_caps(STREAM s)
{
	uint16 width, height, depth;

	in_uint16_le(s, depth);
	in_uint8s(s, 6);

	in_uint16_le(s, width);
	in_uint16_le(s, height);

	DEBUG(("setting desktop size and depth to: %dx%dx%d\n", width, height, depth));

	/*
	 * The server may limit depth and change the size of the desktop (for
	 * example when shadowing another session).
	 */
	if (g_server_depth != depth)
	{
		warning("Remote desktop does not support colour depth %d; falling back to %d\n",
			g_server_depth, depth);
		g_server_depth = depth;
	}
	if (g_width != width || g_height != height)
	{
		warning("Remote desktop changed from %dx%d to %dx%d.\n", g_width, g_height,
			width, height);
		g_width = width;
		g_height = height;
		ui_resize_window();
	}
}