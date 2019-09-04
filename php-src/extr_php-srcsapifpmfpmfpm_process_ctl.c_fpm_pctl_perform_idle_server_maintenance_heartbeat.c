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
struct TYPE_2__ {scalar_t__ parent_pid; scalar_t__ is_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_EV_PERSIST ; 
 short FPM_EV_TIMEOUT ; 
 int /*<<< orphan*/  FPM_IDLE_SERVER_MAINTENANCE_HEARTBEAT ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 int /*<<< orphan*/  fpm_event_add (struct fpm_event_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_event_set_timer (struct fpm_event_s*,int /*<<< orphan*/ ,void (*) (struct fpm_event_s*,short,void*),int /*<<< orphan*/ *) ; 
 TYPE_1__ fpm_globals ; 
 scalar_t__ fpm_pctl_can_spawn_children () ; 
 int /*<<< orphan*/  fpm_pctl_perform_idle_server_maintenance (struct timeval*) ; 
 scalar_t__ getpid () ; 

void fpm_pctl_perform_idle_server_maintenance_heartbeat(struct fpm_event_s *ev, short which, void *arg) /* {{{ */
{
	static struct fpm_event_s heartbeat;
	struct timeval now;

	if (fpm_globals.parent_pid != getpid()) {
		return; /* sanity check */
	}

	if (which == FPM_EV_TIMEOUT) {
		fpm_clock_get(&now);
		if (fpm_pctl_can_spawn_children()) {
			fpm_pctl_perform_idle_server_maintenance(&now);

			/* if it's a child, stop here without creating the next event
			 * this event is reserved to the master process
			 */
			if (fpm_globals.is_child) {
				return;
			}
		}
		return;
	}

	/* first call without setting which to initialize the timer */
	fpm_event_set_timer(&heartbeat, FPM_EV_PERSIST, &fpm_pctl_perform_idle_server_maintenance_heartbeat, NULL);
	fpm_event_add(&heartbeat, FPM_IDLE_SERVER_MAINTENANCE_HEARTBEAT);
}