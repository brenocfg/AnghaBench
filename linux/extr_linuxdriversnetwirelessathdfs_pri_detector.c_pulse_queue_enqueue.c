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
typedef  void* u64 ;
struct pulse_elem {int /*<<< orphan*/  head; void* ts; } ;
struct pri_detector {scalar_t__ count; scalar_t__ max_count; void* last_ts; int /*<<< orphan*/  pulses; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS_POOL_STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pulse_elem* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pulse_elem* pool_get_pulse_elem () ; 
 int /*<<< orphan*/  pulse_alloc_error ; 
 int /*<<< orphan*/  pulse_allocated ; 
 int /*<<< orphan*/  pulse_queue_check_window (struct pri_detector*) ; 
 int /*<<< orphan*/  pulse_queue_dequeue (struct pri_detector*) ; 
 int /*<<< orphan*/  pulse_used ; 

__attribute__((used)) static bool pulse_queue_enqueue(struct pri_detector *pde, u64 ts)
{
	struct pulse_elem *p = pool_get_pulse_elem();
	if (p == NULL) {
		p = kmalloc(sizeof(*p), GFP_ATOMIC);
		if (p == NULL) {
			DFS_POOL_STAT_INC(pulse_alloc_error);
			return false;
		}
		DFS_POOL_STAT_INC(pulse_allocated);
		DFS_POOL_STAT_INC(pulse_used);
	}
	INIT_LIST_HEAD(&p->head);
	p->ts = ts;
	list_add(&p->head, &pde->pulses);
	pde->count++;
	pde->last_ts = ts;
	pulse_queue_check_window(pde);
	if (pde->count >= pde->max_count)
		pulse_queue_dequeue(pde);
	return true;
}