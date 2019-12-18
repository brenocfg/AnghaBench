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
 int /*<<< orphan*/  CONFIG_SECTION_GLOBAL ; 
 int FILENAME_MAX ; 
 void* config_get (int /*<<< orphan*/ ,char*,char*) ; 
 long long config_get_number (int /*<<< orphan*/ ,char*,long long) ; 
 unsigned long error_log_errors_per_period ; 
 unsigned long error_log_errors_per_period_backup ; 
 long long error_log_throttle_period ; 
 void* facility_log ; 
 char* netdata_configured_log_dir ; 
 int /*<<< orphan*/  setenv (char*,void*,int) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*) ; 
 void* stdaccess_filename ; 
 void* stderr_filename ; 
 void* stdout_filename ; 

__attribute__((used)) static void log_init(void) {
    char filename[FILENAME_MAX + 1];
    snprintfz(filename, FILENAME_MAX, "%s/debug.log", netdata_configured_log_dir);
    stdout_filename    = config_get(CONFIG_SECTION_GLOBAL, "debug log",  filename);

    snprintfz(filename, FILENAME_MAX, "%s/error.log", netdata_configured_log_dir);
    stderr_filename    = config_get(CONFIG_SECTION_GLOBAL, "error log",  filename);

    snprintfz(filename, FILENAME_MAX, "%s/access.log", netdata_configured_log_dir);
    stdaccess_filename = config_get(CONFIG_SECTION_GLOBAL, "access log", filename);

    char deffacility[8];
    snprintfz(deffacility,7,"%s","daemon");
    facility_log = config_get(CONFIG_SECTION_GLOBAL, "facility log",  deffacility);

    error_log_throttle_period = config_get_number(CONFIG_SECTION_GLOBAL, "errors flood protection period", error_log_throttle_period);
    error_log_errors_per_period = (unsigned long)config_get_number(CONFIG_SECTION_GLOBAL, "errors to trigger flood protection", (long long int)error_log_errors_per_period);
    error_log_errors_per_period_backup = error_log_errors_per_period;

    setenv("NETDATA_ERRORS_THROTTLE_PERIOD", config_get(CONFIG_SECTION_GLOBAL, "errors flood protection period"    , ""), 1);
    setenv("NETDATA_ERRORS_PER_PERIOD",      config_get(CONFIG_SECTION_GLOBAL, "errors to trigger flood protection", ""), 1);
}