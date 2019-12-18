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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INVERTED ; 
 scalar_t__ VIsual_active ; 
 int /*<<< orphan*/  VIsual_reselect ; 
 int /*<<< orphan*/  end_visual_mode () ; 
 int /*<<< orphan*/  redraw_curbuf_later (int /*<<< orphan*/ ) ; 

void
reset_VIsual()
{
    if (VIsual_active)
    {
	end_visual_mode();
	redraw_curbuf_later(INVERTED);	/* delete the inversion later */
	VIsual_reselect = FALSE;
    }
}