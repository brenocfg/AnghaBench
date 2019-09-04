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
struct bpf_insn_aux_data {int /*<<< orphan*/  map_state; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_MAP_PTR_POISON ; 

__attribute__((used)) static bool bpf_map_ptr_poisoned(const struct bpf_insn_aux_data *aux)
{
	return BPF_MAP_PTR(aux->map_state) == BPF_MAP_PTR_POISON;
}