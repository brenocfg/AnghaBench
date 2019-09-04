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
struct timeval {unsigned long tv_sec; unsigned long tv_usec; } ;
struct fpm_event_s {int index; int flags; int which; struct timeval frequency; } ;

/* Variables and functions */
 int FPM_EV_READ ; 
 int FPM_EV_TIMEOUT ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 scalar_t__ fpm_event_queue_add (int /*<<< orphan*/ *,struct fpm_event_s*) ; 
 int /*<<< orphan*/  fpm_event_queue_fd ; 
 int /*<<< orphan*/  fpm_event_queue_timer ; 
 int /*<<< orphan*/  fpm_event_set_timeout (struct fpm_event_s*,struct timeval) ; 

int fpm_event_add(struct fpm_event_s *ev, unsigned long int frequency) /* {{{ */
{
	struct timeval now;
	struct timeval tmp;

	if (!ev) {
		return -1;
	}

	ev->index = -1;

	/* it's a triggered event on incoming data */
	if (ev->flags & FPM_EV_READ) {
		ev->which = FPM_EV_READ;
		if (fpm_event_queue_add(&fpm_event_queue_fd, ev) != 0) {
			return -1;
		}
		return 0;
	}

	/* it's a timer event */
	ev->which = FPM_EV_TIMEOUT;

	fpm_clock_get(&now);
	if (frequency >= 1000) {
		tmp.tv_sec = frequency / 1000;
		tmp.tv_usec = (frequency % 1000) * 1000;
	} else {
		tmp.tv_sec = 0;
		tmp.tv_usec = frequency * 1000;
	}
	ev->frequency = tmp;
	fpm_event_set_timeout(ev, now);

	if (fpm_event_queue_add(&fpm_event_queue_timer, ev) != 0) {
		return -1;
	}

	return 0;
}