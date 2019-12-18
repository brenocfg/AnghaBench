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
typedef  int /*<<< orphan*/  collected_number ;

/* Variables and functions */
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  error (char*) ; 
 int procfile_lines (scalar_t__) ; 
 int /*<<< orphan*/  procfile_lineword (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int procfile_linewords (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ procfile_open (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ procfile_readall (scalar_t__) ; 
 scalar_t__ read_proc_uptime_ff ; 
 double strtold (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline collected_number read_proc_uptime(char *filename) {
    if(unlikely(!read_proc_uptime_ff)) {
        read_proc_uptime_ff = procfile_open(filename, " \t", PROCFILE_FLAG_DEFAULT);
        if(unlikely(!read_proc_uptime_ff)) return 0;
    }

    read_proc_uptime_ff = procfile_readall(read_proc_uptime_ff);
    if(unlikely(!read_proc_uptime_ff)) return 0;

    if(unlikely(procfile_lines(read_proc_uptime_ff) < 1)) {
        error("/proc/uptime has no lines.");
        return 0;
    }
    if(unlikely(procfile_linewords(read_proc_uptime_ff, 0) < 1)) {
        error("/proc/uptime has less than 1 word in it.");
        return 0;
    }

    return (collected_number)(strtold(procfile_lineword(read_proc_uptime_ff, 0, 0), NULL) * 1000.0);
}