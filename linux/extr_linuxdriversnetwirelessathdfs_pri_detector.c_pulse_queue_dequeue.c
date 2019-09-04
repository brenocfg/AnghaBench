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
struct pulse_elem {int /*<<< orphan*/  head; } ;
struct pri_detector {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_put_pulse_elem (struct pulse_elem*) ; 
 struct pulse_elem* pulse_queue_get_tail (struct pri_detector*) ; 

__attribute__((used)) static bool pulse_queue_dequeue(struct pri_detector *pde)
{
	struct pulse_elem *p = pulse_queue_get_tail(pde);
	if (p != NULL) {
		list_del_init(&p->head);
		pde->count--;
		/* give it back to pool */
		pool_put_pulse_elem(p);
	}
	return (pde->count > 0);
}