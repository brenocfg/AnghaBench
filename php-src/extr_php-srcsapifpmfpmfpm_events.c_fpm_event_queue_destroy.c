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
struct fpm_event_queue_s {struct fpm_event_queue_s* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clean ) () ;} ;

/* Variables and functions */
 struct fpm_event_queue_s* fpm_event_queue_fd ; 
 int /*<<< orphan*/  free (struct fpm_event_queue_s*) ; 
 TYPE_1__* module ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void fpm_event_queue_destroy(struct fpm_event_queue_s **queue) /* {{{ */
{
	struct fpm_event_queue_s *q, *tmp;

	if (!queue) {
		return;
	}

	if (*queue == fpm_event_queue_fd && module->clean) {
		module->clean();
	}

	q = *queue;
	while (q) {
		tmp = q;
		q = q->next;
		/* q->prev = NULL */
		free(tmp);
	}
	*queue = NULL;
}