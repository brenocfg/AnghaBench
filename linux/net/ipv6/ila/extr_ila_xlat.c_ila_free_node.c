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
struct ila_map {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ila_release (struct ila_map*) ; 
 struct ila_map* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ila_free_node(struct ila_map *ila)
{
	struct ila_map *next;

	/* Assume rcu_readlock held */
	while (ila) {
		next = rcu_access_pointer(ila->next);
		ila_release(ila);
		ila = next;
	}
}