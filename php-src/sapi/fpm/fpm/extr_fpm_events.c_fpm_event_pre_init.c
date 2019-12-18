#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_ERROR ; 
 TYPE_1__* fpm_event_devpoll_module () ; 
 TYPE_1__* fpm_event_epoll_module () ; 
 TYPE_1__* fpm_event_kqueue_module () ; 
 TYPE_1__* fpm_event_poll_module () ; 
 TYPE_1__* fpm_event_port_module () ; 
 TYPE_1__* fpm_event_select_module () ; 
 TYPE_1__* module ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

int fpm_event_pre_init(char *machanism) /* {{{ */
{
	/* kqueue */
	module = fpm_event_kqueue_module();
	if (module) {
		if (!machanism || strcasecmp(module->name, machanism) == 0) {
			return 0;
		}
	}

	/* port */
	module = fpm_event_port_module();
	if (module) {
		if (!machanism || strcasecmp(module->name, machanism) == 0) {
			return 0;
		}
	}

	/* epoll */
	module = fpm_event_epoll_module();
	if (module) {
		if (!machanism || strcasecmp(module->name, machanism) == 0) {
			return 0;
		}
	}

	/* /dev/poll */
	module = fpm_event_devpoll_module();
	if (module) {
		if (!machanism || strcasecmp(module->name, machanism) == 0) {
			return 0;
		}
	}

	/* poll */
	module = fpm_event_poll_module();
	if (module) {
		if (!machanism || strcasecmp(module->name, machanism) == 0) {
			return 0;
		}
	}

	/* select */
	module = fpm_event_select_module();
	if (module) {
		if (!machanism || strcasecmp(module->name, machanism) == 0) {
			return 0;
		}
	}

	if (machanism) {
		zlog(ZLOG_ERROR, "event mechanism '%s' is not available on this system", machanism);
	} else {
		zlog(ZLOG_ERROR, "unable to find a suitable event mechanism on this system");
	}
	return -1;
}