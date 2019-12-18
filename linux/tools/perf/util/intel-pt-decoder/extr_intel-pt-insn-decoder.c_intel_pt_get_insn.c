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
struct intel_pt_insn {int /*<<< orphan*/  buf; } ;
struct insn {size_t length; } ;

/* Variables and functions */
 size_t INTEL_PT_INSN_BUF_SZ ; 
 int /*<<< orphan*/  insn_complete (struct insn*) ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 int /*<<< orphan*/  insn_init (struct insn*,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  intel_pt_insn_decoder (struct insn*,struct intel_pt_insn*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int intel_pt_get_insn(const unsigned char *buf, size_t len, int x86_64,
		      struct intel_pt_insn *intel_pt_insn)
{
	struct insn insn;

	insn_init(&insn, buf, len, x86_64);
	insn_get_length(&insn);
	if (!insn_complete(&insn) || insn.length > len)
		return -1;
	intel_pt_insn_decoder(&insn, intel_pt_insn);
	if (insn.length < INTEL_PT_INSN_BUF_SZ)
		memcpy(intel_pt_insn->buf, buf, insn.length);
	else
		memcpy(intel_pt_insn->buf, buf, INTEL_PT_INSN_BUF_SZ);
	return 0;
}