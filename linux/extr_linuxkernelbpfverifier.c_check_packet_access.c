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
typedef  size_t u32 ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {scalar_t__ smin_value; } ;

/* Variables and functions */
 int EACCES ; 
 int __check_packet_access (struct bpf_verifier_env*,size_t,int,int,int) ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,size_t) ; 

__attribute__((used)) static int check_packet_access(struct bpf_verifier_env *env, u32 regno, int off,
			       int size, bool zero_size_allowed)
{
	struct bpf_reg_state *regs = cur_regs(env);
	struct bpf_reg_state *reg = &regs[regno];
	int err;

	/* We may have added a variable offset to the packet pointer; but any
	 * reg->range we have comes after that.  We are only checking the fixed
	 * offset.
	 */

	/* We don't allow negative numbers, because we aren't tracking enough
	 * detail to prove they're safe.
	 */
	if (reg->smin_value < 0) {
		verbose(env, "R%d min value is negative, either use unsigned index or do a if (index >=0) check.\n",
			regno);
		return -EACCES;
	}
	err = __check_packet_access(env, regno, off, size, zero_size_allowed);
	if (err) {
		verbose(env, "R%d offset is outside of the packet\n", regno);
		return err;
	}
	return err;
}