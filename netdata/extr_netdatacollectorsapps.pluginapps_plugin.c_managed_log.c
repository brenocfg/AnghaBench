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
typedef  int uint32_t ;
struct pid_stat {int log_thrown; char* pid; char* comm; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
#define  PID_LOG_CMDLINE 132 
#define  PID_LOG_FDS 131 
#define  PID_LOG_IO 130 
#define  PID_LOG_STAT 129 
#define  PID_LOG_STATUS 128 
 scalar_t__ debug_enabled ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char*,char*,...) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int managed_log(struct pid_stat *p, uint32_t log, int status) {
    if(unlikely(!status)) {
        // error("command failed log %u, errno %d", log, errno);

        if(unlikely(debug_enabled || errno != ENOENT)) {
            if(unlikely(debug_enabled || !(p->log_thrown & log))) {
                p->log_thrown |= log;
                switch(log) {
                    case PID_LOG_IO:
                        #ifdef __FreeBSD__
                        error("Cannot fetch process %d I/O info (command '%s')", p->pid, p->comm);
                        #else
                        error("Cannot process %s/proc/%d/io (command '%s')", netdata_configured_host_prefix, p->pid, p->comm);
                        #endif
                        break;

                    case PID_LOG_STATUS:
                        #ifdef __FreeBSD__
                        error("Cannot fetch process %d status info (command '%s')", p->pid, p->comm);
                        #else
                        error("Cannot process %s/proc/%d/status (command '%s')", netdata_configured_host_prefix, p->pid, p->comm);
                        #endif
                        break;

                    case PID_LOG_CMDLINE:
                        #ifdef __FreeBSD__
                        error("Cannot fetch process %d command line (command '%s')", p->pid, p->comm);
                        #else
                        error("Cannot process %s/proc/%d/cmdline (command '%s')", netdata_configured_host_prefix, p->pid, p->comm);
                        #endif
                        break;

                    case PID_LOG_FDS:
                        #ifdef __FreeBSD__
                        error("Cannot fetch process %d files (command '%s')", p->pid, p->comm);
                        #else
                        error("Cannot process entries in %s/proc/%d/fd (command '%s')", netdata_configured_host_prefix, p->pid, p->comm);
                        #endif
                        break;

                    case PID_LOG_STAT:
                        break;

                    default:
                        error("unhandled error for pid %d, command '%s'", p->pid, p->comm);
                        break;
                }
            }
        }
        errno = 0;
    }
    else if(unlikely(p->log_thrown & log)) {
        // error("unsetting log %u on pid %d", log, p->pid);
        p->log_thrown &= ~log;
    }

    return status;
}