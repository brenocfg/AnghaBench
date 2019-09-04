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
typedef  scalar_t__ uint64_t ;
struct intel_pt_insn {scalar_t__ branch; scalar_t__ length; } ;
struct intel_pt_decoder {int flags; scalar_t__ ip; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_BR_INDIRECT ; 
 int INTEL_PT_FUP_WITH_NLIP ; 

__attribute__((used)) static inline bool intel_pt_fup_with_nlip(struct intel_pt_decoder *decoder,
					  struct intel_pt_insn *intel_pt_insn,
					  uint64_t ip, int err)
{
	return decoder->flags & INTEL_PT_FUP_WITH_NLIP && !err &&
	       intel_pt_insn->branch == INTEL_PT_BR_INDIRECT &&
	       ip == decoder->ip + intel_pt_insn->length;
}