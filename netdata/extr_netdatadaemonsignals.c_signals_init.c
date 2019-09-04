#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;
struct TYPE_2__ {scalar_t__ action; int /*<<< orphan*/  name; int /*<<< orphan*/  signo; } ;

/* Variables and functions */
 scalar_t__ NETDATA_SIGNAL_END_OF_LIST ; 
 scalar_t__ NETDATA_SIGNAL_IGNORE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 TYPE_1__* signals_waiting ; 

void signals_init(void) {
    // Catch signals which we want to use
    struct sigaction sa;
    sa.sa_flags = 0;

    // ignore all signals while we run in a signal handler
    sigfillset(&sa.sa_mask);

    int i;
    for (i = 0; signals_waiting[i].action != NETDATA_SIGNAL_END_OF_LIST; i++) {
        if(signals_waiting[i].action == NETDATA_SIGNAL_IGNORE)
            sa.sa_handler = SIG_IGN;
        else
            sa.sa_handler = signal_handler;

        if(sigaction(signals_waiting[i].signo, &sa, NULL) == -1)
            error("SIGNAL: Failed to change signal handler for: %s", signals_waiting[i].name);
    }
}