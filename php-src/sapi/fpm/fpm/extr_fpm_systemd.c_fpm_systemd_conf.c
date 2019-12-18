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
struct TYPE_2__ {int systemd_interval; int systemd_watchdog; } ;

/* Variables and functions */
 int FPM_SYSTEMD_DEFAULT_HEARTBEAT ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 long atol (char*) ; 
 TYPE_1__ fpm_global_config ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

int fpm_systemd_conf() /* {{{ */
{
	char *watchdog;
	int  interval = 0;

	watchdog = getenv("WATCHDOG_USEC");
	if (watchdog) {
		/* usec to msec, and half the configured delay */
		interval = (int)(atol(watchdog) / 2000L);
		zlog(ZLOG_DEBUG, "WATCHDOG_USEC=%s, interval=%d", watchdog, interval);
	}

	if (interval > 1000) {
		if (fpm_global_config.systemd_interval > 0) {
			zlog(ZLOG_WARNING, "systemd_interval option ignored");
		}
		zlog(ZLOG_NOTICE, "systemd watchdog configured to %.3gsec", (float)interval / 1000.0);
		fpm_global_config.systemd_watchdog = 1;
		fpm_global_config.systemd_interval = interval;

	} else if (fpm_global_config.systemd_interval < 0) {
		/* not set => default value */
		fpm_global_config.systemd_interval = FPM_SYSTEMD_DEFAULT_HEARTBEAT;

	} else {
		/* sec to msec */
		fpm_global_config.systemd_interval *= 1000;
	}
	return 0;
}