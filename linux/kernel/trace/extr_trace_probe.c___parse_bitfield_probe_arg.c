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
struct fetch_type {int /*<<< orphan*/  size; } ;
struct fetch_insn {scalar_t__ op; unsigned long lshift; unsigned long rshift; int /*<<< orphan*/  basesize; } ;

/* Variables and functions */
 unsigned long BYTES_TO_BITS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ FETCH_OP_MOD_BF ; 
 scalar_t__ FETCH_OP_NOP ; 
 unsigned long simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __parse_bitfield_probe_arg(const char *bf,
				      const struct fetch_type *t,
				      struct fetch_insn **pcode)
{
	struct fetch_insn *code = *pcode;
	unsigned long bw, bo;
	char *tail;

	if (*bf != 'b')
		return 0;

	bw = simple_strtoul(bf + 1, &tail, 0);	/* Use simple one */

	if (bw == 0 || *tail != '@')
		return -EINVAL;

	bf = tail + 1;
	bo = simple_strtoul(bf, &tail, 0);

	if (tail == bf || *tail != '/')
		return -EINVAL;
	code++;
	if (code->op != FETCH_OP_NOP)
		return -EINVAL;
	*pcode = code;

	code->op = FETCH_OP_MOD_BF;
	code->lshift = BYTES_TO_BITS(t->size) - (bw + bo);
	code->rshift = BYTES_TO_BITS(t->size) - bw;
	code->basesize = t->size;

	return (BYTES_TO_BITS(t->size) < (bw + bo)) ? -EINVAL : 0;
}