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
struct ab8500_fg {int /*<<< orphan*/  ab8500_fg_complete; } ;

/* Variables and functions */
 int completion_done (int /*<<< orphan*/ *) ; 

int ab8500_fg_inst_curr_done(struct ab8500_fg *di)
{
	return completion_done(&di->ab8500_fg_complete);
}