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
struct probe_arg {struct fetch_insn* fmt; struct fetch_insn* comm; struct fetch_insn* name; struct fetch_insn* code; } ;
struct fetch_insn {scalar_t__ op; struct fetch_insn* data; } ;

/* Variables and functions */
 scalar_t__ FETCH_NOP_SYMBOL ; 
 scalar_t__ FETCH_OP_DATA ; 
 scalar_t__ FETCH_OP_END ; 
 int /*<<< orphan*/  kfree (struct fetch_insn*) ; 

void traceprobe_free_probe_arg(struct probe_arg *arg)
{
	struct fetch_insn *code = arg->code;

	while (code && code->op != FETCH_OP_END) {
		if (code->op == FETCH_NOP_SYMBOL ||
		    code->op == FETCH_OP_DATA)
			kfree(code->data);
		code++;
	}
	kfree(arg->code);
	kfree(arg->name);
	kfree(arg->comm);
	kfree(arg->fmt);
}