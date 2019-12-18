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
struct qlist_head {scalar_t__ bytes; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */

__attribute__((used)) static void qlist_init(struct qlist_head *q)
{
	q->head = q->tail = NULL;
	q->bytes = 0;
}