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
typedef  char* pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 char* pid_max ; 
 scalar_t__ read_single_number_file (char*,unsigned long long*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (char) ; 

pid_t get_system_pid_max(void) {
#ifdef __APPLE__
    // As we currently do not know a solution to query pid_max from the os
        // we use the number defined in bsd/sys/proc_internal.h in XNU sources
        pid_max = 99999;
        return pid_max;
#elif __FreeBSD__
    int32_t tmp_pid_max;

        if (unlikely(GETSYSCTL_BY_NAME("kern.pid_max", tmp_pid_max))) {
            pid_max = 99999;
            error("Assuming system's maximum pid is %d.", pid_max);
        } else {
            pid_max = tmp_pid_max;
        }

        return pid_max;
#else

    static char read = 0;
    if(unlikely(read)) return pid_max;
    read = 1;

    char filename[FILENAME_MAX + 1];
    snprintfz(filename, FILENAME_MAX, "%s/proc/sys/kernel/pid_max", netdata_configured_host_prefix);

    unsigned long long max = 0;
    if(read_single_number_file(filename, &max) != 0) {
        error("Cannot open file '%s'. Assuming system supports %d pids.", filename, pid_max);
        return pid_max;
    }

    if(!max) {
        error("Cannot parse file '%s'. Assuming system supports %d pids.", filename, pid_max);
        return pid_max;
    }

    pid_max = (pid_t) max;
    return pid_max;

#endif /* __APPLE__, __FreeBSD__ */
}