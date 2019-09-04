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

/* Variables and functions */
 scalar_t__ must_redraw ; 
 int /*<<< orphan*/  update_screen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_topline () ; 

void
update_topline_redraw()
{
    update_topline();
    if (must_redraw)
	update_screen(0);
}