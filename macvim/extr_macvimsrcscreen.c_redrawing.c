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
 int /*<<< orphan*/  KeyTyped ; 
 int /*<<< orphan*/  RedrawingDisabled ; 
 scalar_t__ char_avail () ; 
 int /*<<< orphan*/  do_redraw ; 
 scalar_t__ p_lz ; 

int
redrawing()
{
    return (!RedrawingDisabled
		       && !(p_lz && char_avail() && !KeyTyped && !do_redraw));
}