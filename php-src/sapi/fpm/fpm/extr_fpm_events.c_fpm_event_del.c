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
struct fpm_event_s {scalar_t__ index; } ;

/* Variables and functions */
 scalar_t__ fpm_event_queue_del (int /*<<< orphan*/ *,struct fpm_event_s*) ; 
 int /*<<< orphan*/  fpm_event_queue_fd ; 
 int /*<<< orphan*/  fpm_event_queue_timer ; 

int fpm_event_del(struct fpm_event_s *ev) /* {{{ */
{
	if (ev->index >= 0 && fpm_event_queue_del(&fpm_event_queue_fd, ev) != 0) {
		return -1;
	}

	if (ev->index < 0 && fpm_event_queue_del(&fpm_event_queue_timer, ev) != 0) {
		return -1;
	}

	return 0;
}