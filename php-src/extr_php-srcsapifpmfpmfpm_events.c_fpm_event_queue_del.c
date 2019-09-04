#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpm_event_s {int dummy; } ;
struct fpm_event_queue_s {struct fpm_event_queue_s* next; TYPE_1__* prev; struct fpm_event_s* ev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* remove ) (struct fpm_event_s*) ;} ;
struct TYPE_3__ {struct fpm_event_queue_s* next; } ;

/* Variables and functions */
 struct fpm_event_queue_s* fpm_event_queue_fd ; 
 int /*<<< orphan*/  free (struct fpm_event_queue_s*) ; 
 TYPE_2__* module ; 
 int /*<<< orphan*/  stub1 (struct fpm_event_s*) ; 

__attribute__((used)) static int fpm_event_queue_del(struct fpm_event_queue_s **queue, struct fpm_event_s *ev) /* {{{ */
{
	struct fpm_event_queue_s *q;
	if (!queue || !ev) {
		return -1;
	}
	q = *queue;
	while (q) {
		if (q->ev == ev) {
			if (q->prev) {
				q->prev->next = q->next;
			}
			if (q->next) {
				q->next->prev = q->prev;
			}
			if (q == *queue) {
				*queue = q->next;
				if (*queue) {
					(*queue)->prev = NULL;
				}
			}

			/* ask the event module to remove the fd from its own queue */
			if (*queue == fpm_event_queue_fd && module->remove) {
				module->remove(ev);
			}

			free(q);
			return 0;
		}
		q = q->next;
	}
	return -1;
}