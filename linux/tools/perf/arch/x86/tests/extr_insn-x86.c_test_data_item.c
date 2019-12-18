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
struct test_data {int /*<<< orphan*/  asm_rep; int /*<<< orphan*/  expected_rel; int /*<<< orphan*/  data; int /*<<< orphan*/  expected_branch_str; int /*<<< orphan*/  expected_op_str; int /*<<< orphan*/  expected_length; } ;
struct intel_pt_insn {int /*<<< orphan*/  rel; scalar_t__ branch; scalar_t__ op; } ;
struct insn {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_INSN_SIZE ; 
 int get_branch (int /*<<< orphan*/ ) ; 
 int get_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insn_complete (struct insn*) ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 int /*<<< orphan*/  insn_init (struct insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_pt_get_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct intel_pt_insn*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int test_data_item(struct test_data *dat, int x86_64)
{
	struct intel_pt_insn intel_pt_insn;
	struct insn insn;
	int op, branch;

	insn_init(&insn, dat->data, MAX_INSN_SIZE, x86_64);
	insn_get_length(&insn);

	if (!insn_complete(&insn)) {
		pr_debug("Failed to decode: %s\n", dat->asm_rep);
		return -1;
	}

	if (insn.length != dat->expected_length) {
		pr_debug("Failed to decode length (%d vs expected %d): %s\n",
			 insn.length, dat->expected_length, dat->asm_rep);
		return -1;
	}

	op = get_op(dat->expected_op_str);
	branch = get_branch(dat->expected_branch_str);

	if (intel_pt_get_insn(dat->data, MAX_INSN_SIZE, x86_64, &intel_pt_insn)) {
		pr_debug("Intel PT failed to decode: %s\n", dat->asm_rep);
		return -1;
	}

	if ((int)intel_pt_insn.op != op) {
		pr_debug("Failed to decode 'op' value (%d vs expected %d): %s\n",
			 intel_pt_insn.op, op, dat->asm_rep);
		return -1;
	}

	if ((int)intel_pt_insn.branch != branch) {
		pr_debug("Failed to decode 'branch' value (%d vs expected %d): %s\n",
			 intel_pt_insn.branch, branch, dat->asm_rep);
		return -1;
	}

	if (intel_pt_insn.rel != dat->expected_rel) {
		pr_debug("Failed to decode 'rel' value (%#x vs expected %#x): %s\n",
			 intel_pt_insn.rel, dat->expected_rel, dat->asm_rep);
		return -1;
	}

	pr_debug("Decoded ok: %s\n", dat->asm_rep);

	return 0;
}