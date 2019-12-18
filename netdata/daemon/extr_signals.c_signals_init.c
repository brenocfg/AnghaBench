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
struct TYPE_2__ {int action; int /*<<< orphan*/  name; int /*<<< orphan*/  signo; } ;

/* Variables and functions */
#define  NETDATA_SIGNAL_CHILD 129 
 int NETDATA_SIGNAL_END_OF_LIST ; 
#define  NETDATA_SIGNAL_IGNORE 128 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  myp_init () ; 
 int reaper_enabled ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 TYPE_1__* signals_waiting ; 

void signals_init(void) {
    // Catch signals which we want to use
    struct sigaction sa;
    sa.sa_flags = 0;

    // Enable process tracking / reaper if running as init (pid == 1).
    // This prevents zombie processes when running in a container.
    if (getpid() == 1) {
        info("SIGNAL: Enabling reaper");
        myp_init();
        reaper_enabled = 1;
    } else {
        info("SIGNAL: Not enabling reaper");
    }

    // ignore all signals while we run in a signal handler
    sigfillset(&sa.sa_mask);

    int i;
    for (i = 0; signals_waiting[i].action != NETDATA_SIGNAL_END_OF_LIST; i++) {
        switch (signals_waiting[i].action) {
        case NETDATA_SIGNAL_IGNORE:
            sa.sa_handler = SIG_IGN;
            break;
        case NETDATA_SIGNAL_CHILD:
            if (reaper_enabled == 0)
                continue;
            // FALLTHROUGH
        default:
            sa.sa_handler = signal_handler;
            break;
        }

        if(sigaction(signals_waiting[i].signo, &sa, NULL) == -1)
            error("SIGNAL: Failed to change signal handler for: %s", signals_waiting[i].name);
    }
}