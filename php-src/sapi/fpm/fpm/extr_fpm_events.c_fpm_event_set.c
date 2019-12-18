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
struct fpm_event_s {int fd; void (* callback ) (struct fpm_event_s*,short,void*) ;int flags; void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct fpm_event_s*,int /*<<< orphan*/ ,int) ; 

int fpm_event_set(struct fpm_event_s *ev, int fd, int flags, void (*callback)(struct fpm_event_s *, short, void *), void *arg) /* {{{ */
{
	if (!ev || !callback || fd < -1) {
		return -1;
	}
	memset(ev, 0, sizeof(struct fpm_event_s));
	ev->fd = fd;
	ev->callback = callback;
	ev->arg = arg;
	ev->flags = flags;
	return 0;
}