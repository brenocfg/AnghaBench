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
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_LOCAL0 ; 
 int LOG_NDELAY ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_UPTO (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_on ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlogmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_syslog(void)
{
	if (debug_on)
		setlogmask(LOG_UPTO(LOG_DEBUG));
	else
		setlogmask(LOG_UPTO(LOG_ERR));
	openlog("tmon.log", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
	syslog(LOG_NOTICE, "TMON started by User %d", getuid());
}