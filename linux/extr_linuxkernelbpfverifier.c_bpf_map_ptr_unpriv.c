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
struct bpf_insn_aux_data {int map_state; } ;

/* Variables and functions */
 int BPF_MAP_PTR_UNPRIV ; 

__attribute__((used)) static bool bpf_map_ptr_unpriv(const struct bpf_insn_aux_data *aux)
{
	return aux->map_state & BPF_MAP_PTR_UNPRIV;
}