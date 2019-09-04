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
 int /*<<< orphan*/  may_start_select (char) ; 
 int /*<<< orphan*/  n_start_visual_mode (char) ; 

void
start_selection()
{
    /* if 'selectmode' contains "key", start Select mode */
    may_start_select('k');
    n_start_visual_mode('v');
}