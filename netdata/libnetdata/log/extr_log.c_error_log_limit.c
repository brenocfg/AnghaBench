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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int LOG_DATE_LENGTH ; 
 unsigned long error_log_errors_per_period ; 
 scalar_t__ error_log_throttle_period ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  log_date (char*,int) ; 
 scalar_t__ now_monotonic_sec () ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

int error_log_limit(int reset) {
    static time_t start = 0;
    static unsigned long counter = 0, prevented = 0;

    // fprintf(stderr, "FLOOD: counter=%lu, allowed=%lu, backup=%lu, period=%llu\n", counter, error_log_errors_per_period, error_log_errors_per_period_backup, (unsigned long long)error_log_throttle_period);

    // do not throttle if the period is 0
    if(error_log_throttle_period == 0)
        return 0;

    // prevent all logs if the errors per period is 0
    if(error_log_errors_per_period == 0)
#ifdef NETDATA_INTERNAL_CHECKS
        return 0;
#else
        return 1;
#endif

    time_t now = now_monotonic_sec();
    if(!start) start = now;

    if(reset) {
        if(prevented) {
            char date[LOG_DATE_LENGTH];
            log_date(date, LOG_DATE_LENGTH);
            fprintf(stderr, "%s: %s LOG FLOOD PROTECTION reset for process '%s' (prevented %lu logs in the last %ld seconds).\n"
                    , date
                    , program_name
                    , program_name
                    , prevented
                    , now - start
            );
        }

        start = now;
        counter = 0;
        prevented = 0;
    }

    // detect if we log too much
    counter++;

    if(now - start > error_log_throttle_period) {
        if(prevented) {
            char date[LOG_DATE_LENGTH];
            log_date(date, LOG_DATE_LENGTH);
            fprintf(stderr, "%s: %s LOG FLOOD PROTECTION resuming logging from process '%s' (prevented %lu logs in the last %ld seconds).\n"
                    , date
                    , program_name
                    , program_name
                    , prevented
                    , error_log_throttle_period
            );
        }

        // restart the period accounting
        start = now;
        counter = 1;
        prevented = 0;

        // log this error
        return 0;
    }

    if(counter > error_log_errors_per_period) {
        if(!prevented) {
            char date[LOG_DATE_LENGTH];
            log_date(date, LOG_DATE_LENGTH);
            fprintf(stderr, "%s: %s LOG FLOOD PROTECTION too many logs (%lu logs in %ld seconds, threshold is set to %lu logs in %ld seconds). Preventing more logs from process '%s' for %ld seconds.\n"
                    , date
                    , program_name
                    , counter
                    , now - start
                    , error_log_errors_per_period
                    , error_log_throttle_period
                    , program_name
                    , start + error_log_throttle_period - now);
        }

        prevented++;

        // prevent logging this error
#ifdef NETDATA_INTERNAL_CHECKS
        return 0;
#else
        return 1;
#endif
    }

    return 0;
}