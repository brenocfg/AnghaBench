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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

void sigsetup(void)
{
    struct sigaction sa;

    /*
     * Catch at most once, and don't restart the accept system call.
     */
    sa.sa_flags = SA_RESETHAND;
    sa.sa_handler = interrupt;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}