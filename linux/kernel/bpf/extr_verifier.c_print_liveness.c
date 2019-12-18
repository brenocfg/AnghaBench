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
struct bpf_verifier_env {int dummy; } ;
typedef  enum bpf_reg_liveness { ____Placeholder_bpf_reg_liveness } bpf_reg_liveness ;

/* Variables and functions */
 int REG_LIVE_DONE ; 
 int REG_LIVE_READ ; 
 int REG_LIVE_WRITTEN ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static void print_liveness(struct bpf_verifier_env *env,
			   enum bpf_reg_liveness live)
{
	if (live & (REG_LIVE_READ | REG_LIVE_WRITTEN | REG_LIVE_DONE))
	    verbose(env, "_");
	if (live & REG_LIVE_READ)
		verbose(env, "r");
	if (live & REG_LIVE_WRITTEN)
		verbose(env, "w");
	if (live & REG_LIVE_DONE)
		verbose(env, "D");
}