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
typedef  int /*<<< orphan*/  uint64_t ;
struct intel_pt_insn {size_t length; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 size_t INTEL_PT_INSN_BUF_SZ ; 
 int INTEL_PT_INSN_DESC_MAX ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ intel_pt_insn_desc (struct intel_pt_insn*,char*,int) ; 
 scalar_t__ intel_pt_log_open () ; 
 int /*<<< orphan*/  intel_pt_print_data (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 

void __intel_pt_log_insn(struct intel_pt_insn *intel_pt_insn, uint64_t ip)
{
	char desc[INTEL_PT_INSN_DESC_MAX];
	size_t len = intel_pt_insn->length;

	if (intel_pt_log_open())
		return;

	if (len > INTEL_PT_INSN_BUF_SZ)
		len = INTEL_PT_INSN_BUF_SZ;
	intel_pt_print_data(intel_pt_insn->buf, len, ip, 8);
	if (intel_pt_insn_desc(intel_pt_insn, desc, INTEL_PT_INSN_DESC_MAX) > 0)
		fprintf(f, "%s\n", desc);
	else
		fprintf(f, "Bad instruction!\n");
}