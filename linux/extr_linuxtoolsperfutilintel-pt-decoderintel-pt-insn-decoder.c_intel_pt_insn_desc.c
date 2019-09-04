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
struct intel_pt_insn {int branch; int /*<<< orphan*/  op; int /*<<< orphan*/  rel; } ;

/* Variables and functions */
#define  INTEL_PT_BR_CONDITIONAL 131 
#define  INTEL_PT_BR_INDIRECT 130 
#define  INTEL_PT_BR_NO_BRANCH 129 
#define  INTEL_PT_BR_UNCONDITIONAL 128 
 char* intel_pt_insn_name (int /*<<< orphan*/ ) ; 
 int snprintf (char*,size_t,char*,char*,...) ; 

int intel_pt_insn_desc(const struct intel_pt_insn *intel_pt_insn, char *buf,
		       size_t buf_len)
{
	switch (intel_pt_insn->branch) {
	case INTEL_PT_BR_CONDITIONAL:
	case INTEL_PT_BR_UNCONDITIONAL:
		return snprintf(buf, buf_len, "%s %s%d",
				intel_pt_insn_name(intel_pt_insn->op),
				intel_pt_insn->rel > 0 ? "+" : "",
				intel_pt_insn->rel);
	case INTEL_PT_BR_NO_BRANCH:
	case INTEL_PT_BR_INDIRECT:
		return snprintf(buf, buf_len, "%s",
				intel_pt_insn_name(intel_pt_insn->op));
	default:
		break;
	}
	return 0;
}