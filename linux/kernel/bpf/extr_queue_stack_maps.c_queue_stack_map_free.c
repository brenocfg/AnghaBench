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
struct bpf_queue_stack {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_map_area_free (struct bpf_queue_stack*) ; 
 struct bpf_queue_stack* bpf_queue_stack (struct bpf_map*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void queue_stack_map_free(struct bpf_map *map)
{
	struct bpf_queue_stack *qs = bpf_queue_stack(map);

	/* at this point bpf_prog->aux->refcnt == 0 and this map->refcnt == 0,
	 * so the programs (can be more than one that used this map) were
	 * disconnected from events. Wait for outstanding critical sections in
	 * these programs to complete
	 */
	synchronize_rcu();

	bpf_map_area_free(qs);
}