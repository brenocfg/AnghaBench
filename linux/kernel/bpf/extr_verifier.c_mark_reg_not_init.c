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
typedef  scalar_t__ u32 ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ BPF_REG_FP ; 
 scalar_t__ MAX_BPF_REG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __mark_reg_not_init (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,scalar_t__) ; 

__attribute__((used)) static void mark_reg_not_init(struct bpf_verifier_env *env,
			      struct bpf_reg_state *regs, u32 regno)
{
	if (WARN_ON(regno >= MAX_BPF_REG)) {
		verbose(env, "mark_reg_not_init(regs, %u)\n", regno);
		/* Something bad happened, let's kill all regs except FP */
		for (regno = 0; regno < BPF_REG_FP; regno++)
			__mark_reg_not_init(regs + regno);
		return;
	}
	__mark_reg_not_init(regs + regno);
}