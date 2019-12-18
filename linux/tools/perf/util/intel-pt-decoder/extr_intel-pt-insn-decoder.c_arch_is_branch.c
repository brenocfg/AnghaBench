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
struct intel_pt_insn {scalar_t__ branch; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_BR_NO_BRANCH ; 
 scalar_t__ intel_pt_get_insn (unsigned char const*,size_t,int,struct intel_pt_insn*) ; 

int arch_is_branch(const unsigned char *buf, size_t len, int x86_64)
{
	struct intel_pt_insn in;
	if (intel_pt_get_insn(buf, len, x86_64, &in) < 0)
		return -1;
	return in.branch != INTEL_PT_BR_NO_BRANCH;
}