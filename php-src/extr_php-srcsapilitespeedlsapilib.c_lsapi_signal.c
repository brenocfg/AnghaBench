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
struct sigaction {scalar_t__ sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  scalar_t__ sighandler_t ;

/* Variables and functions */
 scalar_t__ SIG_DFL ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lsapi_signal(int signo, sighandler_t handler)
{
    struct sigaction sa;

    sigaction(signo, NULL, &sa);

    if (sa.sa_handler == SIG_DFL)
    {
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = handler;
        sigaction(signo, &sa, NULL);
    }
}