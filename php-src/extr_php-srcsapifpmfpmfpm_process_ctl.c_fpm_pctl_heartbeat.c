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
struct timeval {int dummy; } ;
struct fpm_event_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ parent_pid; int /*<<< orphan*/  heartbeat; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_EV_PERSIST ; 
 short FPM_EV_TIMEOUT ; 
 int /*<<< orphan*/  FPM_PCTL_MIN_HEARTBEAT ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 int /*<<< orphan*/  fpm_event_add (struct fpm_event_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_event_set_timer (struct fpm_event_s*,int /*<<< orphan*/ ,void (*) (struct fpm_event_s*,short,void*),int /*<<< orphan*/ *) ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pctl_check_request_timeout (struct timeval*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void fpm_pctl_heartbeat(struct fpm_event_s *ev, short which, void *arg) /* {{{ */
{
	static struct fpm_event_s heartbeat;
	struct timeval now;

	if (fpm_globals.parent_pid != getpid()) {
		return; /* sanity check */
	}

	if (which == FPM_EV_TIMEOUT) {
		fpm_clock_get(&now);
		fpm_pctl_check_request_timeout(&now);
		return;
	}

	/* ensure heartbeat is not lower than FPM_PCTL_MIN_HEARTBEAT */
	fpm_globals.heartbeat = MAX(fpm_globals.heartbeat, FPM_PCTL_MIN_HEARTBEAT);

	/* first call without setting to initialize the timer */
	zlog(ZLOG_DEBUG, "heartbeat have been set up with a timeout of %dms", fpm_globals.heartbeat);
	fpm_event_set_timer(&heartbeat, FPM_EV_PERSIST, &fpm_pctl_heartbeat, NULL);
	fpm_event_add(&heartbeat, fpm_globals.heartbeat);
}