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
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_PUTS (int /*<<< orphan*/ ) ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  do_shell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* e_shellempty ; 
 scalar_t__* p_sh ; 

void
suspend_shell()
{
    if (*p_sh == NUL)
	EMSG(_(e_shellempty));
    else
    {
	MSG_PUTS(_("new shell started\n"));
	do_shell(NULL, 0);
    }
}