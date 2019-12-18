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
 int /*<<< orphan*/  cancel_main_threads () ; 
 int /*<<< orphan*/  error (char*,scalar_t__*) ; 
 int /*<<< orphan*/  error_log_limit_unlimited () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 scalar_t__* pidfile ; 
 int /*<<< orphan*/  rrdhost_cleanup_all () ; 
 int /*<<< orphan*/  rrdhost_free_all () ; 
 int /*<<< orphan*/  security_clean_openssl () ; 
 int /*<<< orphan*/  send_statistics (char*,char*,char*) ; 
 scalar_t__ unlink (scalar_t__*) ; 

void netdata_cleanup_and_exit(int ret) {
    // enabling this, is wrong
    // because the threads will be cancelled while cleaning up
    // netdata_exit = 1;

    error_log_limit_unlimited();
    info("EXIT: netdata prepares to exit with code %d...", ret);

    send_statistics("EXIT", ret?"ERROR":"OK","-");

    // cleanup/save the database and exit
    info("EXIT: cleaning up the database...");
    rrdhost_cleanup_all();

    if(!ret) {
        // exit cleanly

        // stop everything
        info("EXIT: stopping master threads...");
        cancel_main_threads();

        // free the database
        info("EXIT: freeing database memory...");
        rrdhost_free_all();
    }

    // unlink the pid
    if(pidfile[0]) {
        info("EXIT: removing netdata PID file '%s'...", pidfile);
        if(unlink(pidfile) != 0)
            error("EXIT: cannot unlink pidfile '%s'.", pidfile);
    }

#ifdef ENABLE_HTTPS
    security_clean_openssl();
#endif

    info("EXIT: all done - netdata is now exiting - bye bye...");
    exit(ret);
}