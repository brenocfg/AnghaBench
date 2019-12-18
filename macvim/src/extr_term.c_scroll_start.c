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
 scalar_t__ NUL ; 
 scalar_t__* T_VE ; 
 scalar_t__* T_VS ; 
 int /*<<< orphan*/  out_str (scalar_t__*) ; 
 int /*<<< orphan*/  screen_start () ; 

void
scroll_start()
{
    if (*T_VS != NUL)
    {
	out_str(T_VS);
	out_str(T_VE);
	screen_start();			/* don't know where cursor is now */
    }
}