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
struct bpf_verifier_env {size_t insn_idx; struct bpf_insn_aux_data* insn_aux_data; } ;
struct bpf_insn_aux_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct bpf_insn_aux_data *cur_aux(struct bpf_verifier_env *env)
{
	return &env->insn_aux_data[env->insn_idx];
}