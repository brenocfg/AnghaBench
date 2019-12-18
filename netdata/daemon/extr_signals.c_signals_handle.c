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
struct TYPE_2__ {int action; char* name; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CHILDS ; 
 scalar_t__ EINTR ; 
#define  NETDATA_SIGNAL_CHILD 133 
 int NETDATA_SIGNAL_END_OF_LIST ; 
#define  NETDATA_SIGNAL_EXIT_CLEANLY 132 
#define  NETDATA_SIGNAL_FATAL 131 
#define  NETDATA_SIGNAL_LOG_ROTATE 130 
#define  NETDATA_SIGNAL_RELOAD_HEALTH 129 
#define  NETDATA_SIGNAL_SAVE_DATABASE 128 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_log_limit_reset () ; 
 int /*<<< orphan*/  error_log_limit_unlimited () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  health_reload () ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  netdata_cleanup_and_exit (int /*<<< orphan*/ ) ; 
 int pause () ; 
 int /*<<< orphan*/  reap_children () ; 
 int /*<<< orphan*/  reopen_all_log_files () ; 
 int /*<<< orphan*/  rrdhost_save_all () ; 
 TYPE_1__* signals_waiting ; 

void signals_handle(void) {
    while(1) {

        // pause()  causes  the calling process (or thread) to sleep until a signal
        // is delivered that either terminates the process or causes the invocation
        // of a signal-catching function.
        if(pause() == -1 && errno == EINTR) {

            // loop once, but keep looping while signals are coming in
            // this is needed because a few operations may take some time
            // so we need to check for new signals before pausing again
            int found = 1;
            while(found) {
                found = 0;

                // execute the actions of the signals
                int i;
                for (i = 0; signals_waiting[i].action != NETDATA_SIGNAL_END_OF_LIST; i++) {
                    if (signals_waiting[i].count) {
                        found = 1;
                        signals_waiting[i].count = 0;
                        const char *name = signals_waiting[i].name;

                        switch (signals_waiting[i].action) {
                            case NETDATA_SIGNAL_RELOAD_HEALTH:
                                error_log_limit_unlimited();
                                info("SIGNAL: Received %s. Reloading HEALTH configuration...", name);
                                health_reload();
                                error_log_limit_reset();
                                break;

                            case NETDATA_SIGNAL_SAVE_DATABASE:
                                error_log_limit_unlimited();
                                info("SIGNAL: Received %s. Saving databases...", name);
                                rrdhost_save_all();
                                info("Databases saved.");
                                error_log_limit_reset();
                                break;

                            case NETDATA_SIGNAL_LOG_ROTATE:
                                error_log_limit_unlimited();
                                info("SIGNAL: Received %s. Reopening all log files...", name);
                                reopen_all_log_files();
                                error_log_limit_reset();
                                break;

                            case NETDATA_SIGNAL_EXIT_CLEANLY:
                                error_log_limit_unlimited();
                                info("SIGNAL: Received %s. Cleaning up to exit...", name);
                                netdata_cleanup_and_exit(0);
                                exit(0);

                            case NETDATA_SIGNAL_FATAL:
                                fatal("SIGNAL: Received %s. netdata now exits.", name);

                            case NETDATA_SIGNAL_CHILD:
                                debug(D_CHILDS, "SIGNAL: Received %s. Reaping...", name);
                                reap_children();
                                break;

                            default:
                                info("SIGNAL: Received %s. No signal handler configured. Ignoring it.", name);
                                break;
                        }
                    }
                }
            }
        }
        else
            error("SIGNAL: pause() returned but it was not interrupted by a signal.");
    }
}