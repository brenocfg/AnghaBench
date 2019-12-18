#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct TYPE_3__ {int pids_cnt; int* pids; } ;
typedef  TYPE_1__ dvb_channel_t ;

/* Variables and functions */
 int DMX_FILTER_SIZE ; 
 char* dvb_strtok_r (char*,char const*,char**) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*) ; 
 scalar_t__ sscanf (char*,char*,int*,int*) ; 

__attribute__((used)) static bool parse_pid_string(struct mp_log *log, char *pid_string,
                             dvb_channel_t *ptr)
{
    if (pid_string[0]) {
        int pcnt = 0;
        /* These tokens also catch vdr-style PID lists.
         * They can contain 123=deu@3,124=eng+jap@4;125
         * 3 and 4 are codes for codec type, =langLeft+langRight is allowed,
         * and ; may separate a dolby channel.
         * With the numChars-test and the full token-list, all is handled
         * gracefully.
         */
        const char *tokens = "+,;";
        char *pidPart;
        char *savePtr = NULL;
        pidPart = dvb_strtok_r(pid_string, tokens, &savePtr);
        while (pidPart != NULL) {
            if (ptr->pids_cnt >= DMX_FILTER_SIZE - 1) {
                mp_verbose(log, "Maximum number of PIDs for one channel "
                                "reached, ignoring further ones!\n");
                return pcnt > 0;
            }
            int numChars = 0;
            int pid = 0;
            pcnt += sscanf(pidPart, "%d%n", &pid, &numChars);
            if (numChars > 0) {
                ptr->pids[ptr->pids_cnt] = pid;
                ptr->pids_cnt++;
            }
            pidPart = dvb_strtok_r(NULL, tokens, &savePtr);
        }
        if (pcnt > 0)
            return true;
    }
    return false;
}