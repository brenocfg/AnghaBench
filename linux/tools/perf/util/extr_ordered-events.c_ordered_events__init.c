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
typedef  scalar_t__ u64 ;
struct ordered_events {void* data; int /*<<< orphan*/  deliver; scalar_t__ cur_alloc_size; scalar_t__ max_alloc_size; int /*<<< orphan*/  to_free; int /*<<< orphan*/  cache; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  ordered_events__deliver_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void ordered_events__init(struct ordered_events *oe, ordered_events__deliver_t deliver,
			  void *data)
{
	INIT_LIST_HEAD(&oe->events);
	INIT_LIST_HEAD(&oe->cache);
	INIT_LIST_HEAD(&oe->to_free);
	oe->max_alloc_size = (u64) -1;
	oe->cur_alloc_size = 0;
	oe->deliver	   = deliver;
	oe->data	   = data;
}