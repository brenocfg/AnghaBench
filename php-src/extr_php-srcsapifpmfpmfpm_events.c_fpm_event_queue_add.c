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
struct fpm_event_s {int dummy; } ;
struct fpm_event_queue_s {struct fpm_event_queue_s* next; struct fpm_event_queue_s* prev; struct fpm_event_s* ev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* add ) (struct fpm_event_s*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 struct fpm_event_queue_s* fpm_event_queue_fd ; 
 scalar_t__ fpm_event_queue_isset (struct fpm_event_queue_s*,struct fpm_event_s*) ; 
 struct fpm_event_queue_s* malloc (int) ; 
 TYPE_1__* module ; 
 int /*<<< orphan*/  stub1 (struct fpm_event_s*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fpm_event_queue_add(struct fpm_event_queue_s **queue, struct fpm_event_s *ev) /* {{{ */
{
	struct fpm_event_queue_s *elt;

	if (!queue || !ev) {
		return -1;
	}

	if (fpm_event_queue_isset(*queue, ev)) {
		return 0;
	}

	if (!(elt = malloc(sizeof(struct fpm_event_queue_s)))) {
		zlog(ZLOG_SYSERROR, "Unable to add the event to queue: malloc() failed");
		return -1;
	}
	elt->prev = NULL;
	elt->next = NULL;
	elt->ev = ev;

	if (*queue) {
		(*queue)->prev = elt;
		elt->next = *queue;
	}
	*queue = elt;

	/* ask the event module to add the fd from its own queue */
	if (*queue == fpm_event_queue_fd && module->add) {
		module->add(ev);
	}

	return 0;
}