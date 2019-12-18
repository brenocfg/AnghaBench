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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_lru {scalar_t__ percpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_common_lru_populate (struct bpf_lru*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_percpu_lru_populate (struct bpf_lru*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bpf_lru_populate(struct bpf_lru *lru, void *buf, u32 node_offset,
		      u32 elem_size, u32 nr_elems)
{
	if (lru->percpu)
		bpf_percpu_lru_populate(lru, buf, node_offset, elem_size,
					nr_elems);
	else
		bpf_common_lru_populate(lru, buf, node_offset, elem_size,
					nr_elems);
}