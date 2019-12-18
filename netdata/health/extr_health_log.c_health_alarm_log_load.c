#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* health_log_filename; int /*<<< orphan*/  hostname; scalar_t__ health_log_entries_written; } ;
typedef  TYPE_1__ RRDHOST ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  health_alarm_log_close (TYPE_1__*) ; 
 int /*<<< orphan*/  health_alarm_log_open (TYPE_1__*) ; 
 int /*<<< orphan*/  health_alarm_log_read (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char*) ; 

inline void health_alarm_log_load(RRDHOST *host) {
    health_alarm_log_close(host);

    char filename[FILENAME_MAX + 1];
    snprintfz(filename, FILENAME_MAX, "%s.old", host->health_log_filename);
    FILE *fp = fopen(filename, "r");
    if(!fp)
        error("HEALTH [%s]: cannot open health file: %s", host->hostname, filename);
    else {
        health_alarm_log_read(host, fp, filename);
        fclose(fp);
    }

    host->health_log_entries_written = 0;
    fp = fopen(host->health_log_filename, "r");
    if(!fp)
        error("HEALTH [%s]: cannot open health file: %s", host->hostname, host->health_log_filename);
    else {
        health_alarm_log_read(host, fp, host->health_log_filename);
        fclose(fp);
    }

    health_alarm_log_open(host);
}