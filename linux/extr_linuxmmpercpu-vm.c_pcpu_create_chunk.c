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
struct vm_struct {scalar_t__ addr; } ;
struct pcpu_chunk {scalar_t__ base_addr; struct vm_struct** data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct pcpu_chunk* pcpu_alloc_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_atom_size ; 
 int /*<<< orphan*/  pcpu_free_chunk (struct pcpu_chunk*) ; 
 struct vm_struct** pcpu_get_vm_areas (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* pcpu_group_offsets ; 
 int /*<<< orphan*/  pcpu_group_sizes ; 
 int /*<<< orphan*/  pcpu_nr_groups ; 
 int /*<<< orphan*/  pcpu_stats_chunk_alloc () ; 
 int /*<<< orphan*/  trace_percpu_create_chunk (scalar_t__) ; 

__attribute__((used)) static struct pcpu_chunk *pcpu_create_chunk(gfp_t gfp)
{
	struct pcpu_chunk *chunk;
	struct vm_struct **vms;

	chunk = pcpu_alloc_chunk(gfp);
	if (!chunk)
		return NULL;

	vms = pcpu_get_vm_areas(pcpu_group_offsets, pcpu_group_sizes,
				pcpu_nr_groups, pcpu_atom_size);
	if (!vms) {
		pcpu_free_chunk(chunk);
		return NULL;
	}

	chunk->data = vms;
	chunk->base_addr = vms[0]->addr - pcpu_group_offsets[0];

	pcpu_stats_chunk_alloc();
	trace_percpu_create_chunk(chunk->base_addr);

	return chunk;
}