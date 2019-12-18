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
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  LLVMJITEventListenerRef ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  LLVMCodeGenLevelAggressive ; 
 int /*<<< orphan*/  LLVMCodeGenLevelNone ; 
 int /*<<< orphan*/  LLVMCodeModelJITDefault ; 
 int /*<<< orphan*/  LLVMCreateGDBRegistrationListener () ; 
 int /*<<< orphan*/  LLVMCreatePerfJITEventListener () ; 
 int /*<<< orphan*/  LLVMCreateTargetMachine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMDisposeMessage (char*) ; 
 char* LLVMGetHostCPUFeatures () ; 
 char* LLVMGetHostCPUName () ; 
 scalar_t__ LLVMGetTargetFromTriple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  LLVMInitializeNativeAsmParser () ; 
 int /*<<< orphan*/  LLVMInitializeNativeAsmPrinter () ; 
 int /*<<< orphan*/  LLVMInitializeNativeTarget () ; 
 int /*<<< orphan*/  LLVMLoadLibraryPermanently (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMOrcCreateInstance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMOrcRegisterJITEventListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMRelocDefault ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  before_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ jit_debugging_support ; 
 scalar_t__ jit_profiling_support ; 
 int /*<<< orphan*/  llvm_create_types () ; 
 int /*<<< orphan*/  llvm_opt0_orc ; 
 int /*<<< orphan*/  llvm_opt0_targetmachine ; 
 int /*<<< orphan*/  llvm_opt3_orc ; 
 int /*<<< orphan*/  llvm_opt3_targetmachine ; 
 int llvm_session_initialized ; 
 int /*<<< orphan*/  llvm_shutdown ; 
 int /*<<< orphan*/  llvm_targetref ; 
 int /*<<< orphan*/  llvm_triple ; 

__attribute__((used)) static void
llvm_session_initialize(void)
{
	MemoryContext oldcontext;
	char	   *error = NULL;
	char	   *cpu = NULL;
	char	   *features = NULL;

	if (llvm_session_initialized)
		return;

	oldcontext = MemoryContextSwitchTo(TopMemoryContext);

	LLVMInitializeNativeTarget();
	LLVMInitializeNativeAsmPrinter();
	LLVMInitializeNativeAsmParser();

	/*
	 * Synchronize types early, as that also includes inferring the target
	 * triple.
	 */
	llvm_create_types();

	if (LLVMGetTargetFromTriple(llvm_triple, &llvm_targetref, &error) != 0)
	{
		elog(FATAL, "failed to query triple %s\n", error);
	}

	/*
	 * We want the generated code to use all available features. Therefore
	 * grab the host CPU string and detect features of the current CPU. The
	 * latter is needed because some CPU architectures default to enabling
	 * features not all CPUs have (weird, huh).
	 */
	cpu = LLVMGetHostCPUName();
	features = LLVMGetHostCPUFeatures();
	elog(DEBUG2, "LLVMJIT detected CPU \"%s\", with features \"%s\"",
		 cpu, features);

	llvm_opt0_targetmachine =
		LLVMCreateTargetMachine(llvm_targetref, llvm_triple, cpu, features,
								LLVMCodeGenLevelNone,
								LLVMRelocDefault,
								LLVMCodeModelJITDefault);
	llvm_opt3_targetmachine =
		LLVMCreateTargetMachine(llvm_targetref, llvm_triple, cpu, features,
								LLVMCodeGenLevelAggressive,
								LLVMRelocDefault,
								LLVMCodeModelJITDefault);

	LLVMDisposeMessage(cpu);
	cpu = NULL;
	LLVMDisposeMessage(features);
	features = NULL;

	/* force symbols in main binary to be loaded */
	LLVMLoadLibraryPermanently(NULL);

	llvm_opt0_orc = LLVMOrcCreateInstance(llvm_opt0_targetmachine);
	llvm_opt3_orc = LLVMOrcCreateInstance(llvm_opt3_targetmachine);

#if defined(HAVE_DECL_LLVMCREATEGDBREGISTRATIONLISTENER) && HAVE_DECL_LLVMCREATEGDBREGISTRATIONLISTENER
	if (jit_debugging_support)
	{
		LLVMJITEventListenerRef l = LLVMCreateGDBRegistrationListener();

		LLVMOrcRegisterJITEventListener(llvm_opt0_orc, l);
		LLVMOrcRegisterJITEventListener(llvm_opt3_orc, l);
	}
#endif
#if defined(HAVE_DECL_LLVMCREATEPERFJITEVENTLISTENER) && HAVE_DECL_LLVMCREATEPERFJITEVENTLISTENER
	if (jit_profiling_support)
	{
		LLVMJITEventListenerRef l = LLVMCreatePerfJITEventListener();

		LLVMOrcRegisterJITEventListener(llvm_opt0_orc, l);
		LLVMOrcRegisterJITEventListener(llvm_opt3_orc, l);
	}
#endif

	before_shmem_exit(llvm_shutdown, 0);

	llvm_session_initialized = true;

	MemoryContextSwitchTo(oldcontext);
}