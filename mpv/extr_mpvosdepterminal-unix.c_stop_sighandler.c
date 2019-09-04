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
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  do_deactivate_getch2 () ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_sighandler(int signum)
{
    do_deactivate_getch2();

    // note: for this signal, we use SA_RESETHAND but do NOT mask signals
    // so this will invoke the default handler
    raise(SIGTSTP);
}