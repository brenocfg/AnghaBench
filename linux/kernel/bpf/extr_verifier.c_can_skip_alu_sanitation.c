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
struct bpf_verifier_env {scalar_t__ allow_ptr_leaks; } ;
struct bpf_insn {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ BPF_K ; 
 scalar_t__ BPF_SRC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool can_skip_alu_sanitation(const struct bpf_verifier_env *env,
				    const struct bpf_insn *insn)
{
	return env->allow_ptr_leaks || BPF_SRC(insn->code) == BPF_K;
}