#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog {TYPE_1__* aux; } ;
typedef  void bpf_map ;
struct TYPE_2__ {int used_map_cnt; void** used_maps; } ;

/* Variables and functions */

__attribute__((used)) static const struct bpf_map *bpf_map_from_imm(const struct bpf_prog *prog,
					      unsigned long addr)
{
	int i;

	for (i = 0; i < prog->aux->used_map_cnt; i++)
		if (prog->aux->used_maps[i] == (void *)addr)
			return prog->aux->used_maps[i];
	return NULL;
}