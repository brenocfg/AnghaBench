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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  ALT_INPUT_LOCK_OFF ; 
 int /*<<< orphan*/  do_cmdline_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * initialFileCmd ; 

void
workshop_postinit()
{
    do_cmdline_cmd((char_u *)initialFileCmd);
    ALT_INPUT_LOCK_OFF;
    free(initialFileCmd);
    initialFileCmd = NULL;
}