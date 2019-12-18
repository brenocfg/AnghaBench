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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ctrlc_pressed ; 
 int /*<<< orphan*/  got_int ; 

void
mch_breakcheck(void)
{
    if (ctrlc_pressed)
    {
	ctrlc_pressed = FALSE;
	got_int = TRUE;
    }
}