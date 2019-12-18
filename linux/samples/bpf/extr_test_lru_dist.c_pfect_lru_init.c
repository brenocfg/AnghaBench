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
struct pfect_lru_node {int dummy; } ;
struct pfect_lru {int map_fd; int free_nodes; unsigned int lru_size; scalar_t__ total; scalar_t__ nr_misses; scalar_t__ nr_unique; scalar_t__ cur_size; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,unsigned int,int /*<<< orphan*/ ) ; 
 int malloc (unsigned int) ; 

__attribute__((used)) static void pfect_lru_init(struct pfect_lru *lru, unsigned int lru_size,
			   unsigned int nr_possible_elems)
{
	lru->map_fd = bpf_create_map(BPF_MAP_TYPE_HASH,
				     sizeof(unsigned long long),
				     sizeof(struct pfect_lru_node *),
				     nr_possible_elems, 0);
	assert(lru->map_fd != -1);

	lru->free_nodes = malloc(lru_size * sizeof(struct pfect_lru_node));
	assert(lru->free_nodes);

	INIT_LIST_HEAD(&lru->list);
	lru->cur_size = 0;
	lru->lru_size = lru_size;
	lru->nr_unique = lru->nr_misses = lru->total = 0;
}