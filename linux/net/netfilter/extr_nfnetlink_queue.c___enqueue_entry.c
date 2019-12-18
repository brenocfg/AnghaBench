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
struct nfqnl_instance {int /*<<< orphan*/  queue_total; int /*<<< orphan*/  queue_list; } ;
struct nf_queue_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__enqueue_entry(struct nfqnl_instance *queue, struct nf_queue_entry *entry)
{
       list_add_tail(&entry->list, &queue->queue_list);
       queue->queue_total++;
}