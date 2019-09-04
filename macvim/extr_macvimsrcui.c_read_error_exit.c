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
 int /*<<< orphan*/  IObuff ; 
 int /*<<< orphan*/  STRCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  getout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preserve_exit () ; 
 scalar_t__ silent_mode ; 

void
read_error_exit()
{
    if (silent_mode)	/* Normal way to exit for "ex -s" */
	getout(0);
    STRCPY(IObuff, _("Vim: Error reading input, exiting...\n"));
    preserve_exit();
}