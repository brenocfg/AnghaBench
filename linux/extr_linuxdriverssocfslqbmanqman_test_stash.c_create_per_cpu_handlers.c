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
struct hp_handler {int /*<<< orphan*/  node; int /*<<< orphan*/  frame_ptr; int /*<<< orphan*/  addr; int /*<<< orphan*/  processor_id; } ;
struct hp_cpu {int /*<<< orphan*/  handlers; int /*<<< orphan*/  processor_id; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HP_PER_CPU ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  frame_dma ; 
 int /*<<< orphan*/  frame_ptr ; 
 int /*<<< orphan*/  hp_cpu_list ; 
 int /*<<< orphan*/  hp_cpu_list_length ; 
 int /*<<< orphan*/  hp_cpus ; 
 int /*<<< orphan*/  hp_handler_slab ; 
 int /*<<< orphan*/  hp_lock ; 
 struct hp_handler* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hp_cpu* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_per_cpu_handlers(void)
{
	struct hp_handler *handler;
	int loop;
	struct hp_cpu *hp_cpu = this_cpu_ptr(&hp_cpus);

	hp_cpu->processor_id = smp_processor_id();
	spin_lock(&hp_lock);
	list_add_tail(&hp_cpu->node, &hp_cpu_list);
	hp_cpu_list_length++;
	spin_unlock(&hp_lock);
	INIT_LIST_HEAD(&hp_cpu->handlers);
	for (loop = 0; loop < HP_PER_CPU; loop++) {
		handler = kmem_cache_alloc(hp_handler_slab, GFP_KERNEL);
		if (!handler) {
			pr_crit("kmem_cache_alloc() failed");
			WARN_ON(1);
			return -EIO;
		}
		handler->processor_id = hp_cpu->processor_id;
		handler->addr = frame_dma;
		handler->frame_ptr = frame_ptr;
		list_add_tail(&handler->node, &hp_cpu->handlers);
	}
	return 0;
}