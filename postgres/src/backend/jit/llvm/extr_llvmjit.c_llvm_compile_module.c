#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_8__ {int /*<<< orphan*/  emission_counter; int /*<<< orphan*/  optimization_counter; int /*<<< orphan*/  inlining_counter; } ;
struct TYPE_9__ {int flags; TYPE_1__ instr; } ;
struct TYPE_11__ {int compiled; TYPE_2__ base; int /*<<< orphan*/  handles; int /*<<< orphan*/ * module; int /*<<< orphan*/  module_generation; } ;
struct TYPE_10__ {scalar_t__ orc_handle; int /*<<< orphan*/  stack; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  LLVMSharedModuleRef ;
typedef  scalar_t__ LLVMOrcModuleHandle ;
typedef  int /*<<< orphan*/  LLVMOrcJITStackRef ;
typedef  TYPE_3__ LLVMJitHandle ;
typedef  TYPE_4__ LLVMJitContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INSTR_TIME_ACCUM_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_GET_DOUBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMDisposeModule (int /*<<< orphan*/ *) ; 
 scalar_t__ LLVMOrcAddEagerlyCompiledIR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  LLVMOrcDisposeSharedModuleRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMOrcMakeSharedModule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMWriteBitcodeToFile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyProcPid ; 
 int PGJIT_INLINE ; 
 int PGJIT_OPT3 ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhidecontext (int) ; 
 int /*<<< orphan*/  errhidestmt (int) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jit_dump_bitcode ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  llvm_inline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llvm_opt0_orc ; 
 int /*<<< orphan*/  llvm_opt3_orc ; 
 int /*<<< orphan*/  llvm_optimize_module (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llvm_resolve_symbol ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* psprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
llvm_compile_module(LLVMJitContext *context)
{
	LLVMOrcModuleHandle orc_handle;
	MemoryContext oldcontext;
	static LLVMOrcJITStackRef compile_orc;
	instr_time	starttime;
	instr_time	endtime;

	if (context->base.flags & PGJIT_OPT3)
		compile_orc = llvm_opt3_orc;
	else
		compile_orc = llvm_opt0_orc;

	/* perform inlining */
	if (context->base.flags & PGJIT_INLINE)
	{
		INSTR_TIME_SET_CURRENT(starttime);
		llvm_inline(context->module);
		INSTR_TIME_SET_CURRENT(endtime);
		INSTR_TIME_ACCUM_DIFF(context->base.instr.inlining_counter,
							  endtime, starttime);
	}

	if (jit_dump_bitcode)
	{
		char	   *filename;

		filename = psprintf("%u.%zu.bc",
							MyProcPid,
							context->module_generation);
		LLVMWriteBitcodeToFile(context->module, filename);
		pfree(filename);
	}


	/* optimize according to the chosen optimization settings */
	INSTR_TIME_SET_CURRENT(starttime);
	llvm_optimize_module(context, context->module);
	INSTR_TIME_SET_CURRENT(endtime);
	INSTR_TIME_ACCUM_DIFF(context->base.instr.optimization_counter,
						  endtime, starttime);

	if (jit_dump_bitcode)
	{
		char	   *filename;

		filename = psprintf("%u.%zu.optimized.bc",
							MyProcPid,
							context->module_generation);
		LLVMWriteBitcodeToFile(context->module, filename);
		pfree(filename);
	}

	/*
	 * Emit the code. Note that this can, depending on the optimization
	 * settings, take noticeable resources as code emission executes low-level
	 * instruction combining/selection passes etc. Without optimization a
	 * faster instruction selection mechanism is used.
	 */
	INSTR_TIME_SET_CURRENT(starttime);
#if LLVM_VERSION_MAJOR > 6
	{
		if (LLVMOrcAddEagerlyCompiledIR(compile_orc, &orc_handle, context->module,
										llvm_resolve_symbol, NULL))
		{
			elog(ERROR, "failed to JIT module");
		}

		/* LLVMOrcAddEagerlyCompiledIR takes ownership of the module */
	}
#elif LLVM_VERSION_MAJOR > 4
	{
		LLVMSharedModuleRef smod;

		smod = LLVMOrcMakeSharedModule(context->module);
		if (LLVMOrcAddEagerlyCompiledIR(compile_orc, &orc_handle, smod,
										llvm_resolve_symbol, NULL))
		{
			elog(ERROR, "failed to JIT module");
		}
		LLVMOrcDisposeSharedModuleRef(smod);
	}
#else							/* LLVM 4.0 and 3.9 */
	{
		orc_handle = LLVMOrcAddEagerlyCompiledIR(compile_orc, context->module,
												 llvm_resolve_symbol, NULL);
		LLVMDisposeModule(context->module);
	}
#endif
	INSTR_TIME_SET_CURRENT(endtime);
	INSTR_TIME_ACCUM_DIFF(context->base.instr.emission_counter,
						  endtime, starttime);

	context->module = NULL;
	context->compiled = true;

	/* remember emitted code for cleanup and lookups */
	oldcontext = MemoryContextSwitchTo(TopMemoryContext);
	{
		LLVMJitHandle *handle;

		handle = (LLVMJitHandle *) palloc(sizeof(LLVMJitHandle));
		handle->stack = compile_orc;
		handle->orc_handle = orc_handle;

		context->handles = lappend(context->handles, handle);
	}
	MemoryContextSwitchTo(oldcontext);

	ereport(DEBUG1,
			(errmsg("time to inline: %.3fs, opt: %.3fs, emit: %.3fs",
					INSTR_TIME_GET_DOUBLE(context->base.instr.inlining_counter),
					INSTR_TIME_GET_DOUBLE(context->base.instr.optimization_counter),
					INSTR_TIME_GET_DOUBLE(context->base.instr.emission_counter)),
			 errhidestmt(true),
			 errhidecontext(true)));
}