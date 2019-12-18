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
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  getch2_poll () ; 
 int /*<<< orphan*/  setsigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_sighandler ; 

__attribute__((used)) static void continue_sighandler(int signum)
{
    // SA_RESETHAND has reset SIGTSTP, so we need to restore it here
    setsigaction(SIGTSTP, stop_sighandler, SA_RESETHAND, false);

    getch2_poll();
}