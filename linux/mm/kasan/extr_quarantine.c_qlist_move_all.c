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
struct qlist_head {scalar_t__ bytes; TYPE_1__* tail; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlist_empty (struct qlist_head*) ; 
 int /*<<< orphan*/  qlist_init (struct qlist_head*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlist_move_all(struct qlist_head *from, struct qlist_head *to)
{
	if (unlikely(qlist_empty(from)))
		return;

	if (qlist_empty(to)) {
		*to = *from;
		qlist_init(from);
		return;
	}

	to->tail->next = from->head;
	to->tail = from->tail;
	to->bytes += from->bytes;

	qlist_init(from);
}