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
 scalar_t__ Rows ; 
 int /*<<< orphan*/  limit_screen_size () ; 
 scalar_t__ min_rows () ; 

void
check_shellsize()
{
    if (Rows < min_rows())	/* need room for one window and command line */
	Rows = min_rows();
    limit_screen_size();
}