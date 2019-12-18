#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  created_functions; } ;
struct TYPE_4__ {TYPE_1__ instr; } ;
struct LLVMJitContext {int /*<<< orphan*/  counter; int /*<<< orphan*/  module_generation; TYPE_2__ base; int /*<<< orphan*/ * module; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* psprintf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
llvm_expand_funcname(struct LLVMJitContext *context, const char *basename)
{
	Assert(context->module != NULL);

	context->base.instr.created_functions++;

	/*
	 * Previously we used dots to separate, but turns out some tools, e.g.
	 * GDB, don't like that and truncate name.
	 */
	return psprintf("%s_%zu_%d",
					basename,
					context->module_generation,
					context->counter++);
}