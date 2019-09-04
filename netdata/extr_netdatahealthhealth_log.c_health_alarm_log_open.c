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
struct TYPE_3__ {char* health_log_filename; int /*<<< orphan*/  hostname; scalar_t__ health_log_fp; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 scalar_t__ setvbuf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline int health_alarm_log_open(RRDHOST *host) {
    if(host->health_log_fp)
        fclose(host->health_log_fp);

    host->health_log_fp = fopen(host->health_log_filename, "a");

    if(host->health_log_fp) {
        if (setvbuf(host->health_log_fp, NULL, _IOLBF, 0) != 0)
            error("HEALTH [%s]: cannot set line buffering on health log file '%s'.", host->hostname, host->health_log_filename);
        return 0;
    }

    error("HEALTH [%s]: cannot open health log file '%s'. Health data will be lost in case of netdata or server crash.", host->hostname, host->health_log_filename);
    return -1;
}