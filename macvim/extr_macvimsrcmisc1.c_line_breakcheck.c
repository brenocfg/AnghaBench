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
 scalar_t__ BREAKCHECK_SKIP ; 
 scalar_t__ breakcheck_count ; 
 int /*<<< orphan*/  ui_breakcheck () ; 

void
line_breakcheck()
{
    if (++breakcheck_count >= BREAKCHECK_SKIP)
    {
	breakcheck_count = 0;
	ui_breakcheck();
    }
}