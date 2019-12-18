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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  LLVMOrcDisposeInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMOrcUnregisterPerf (int /*<<< orphan*/ *) ; 
 scalar_t__ jit_profiling_support ; 
 int /*<<< orphan*/ * llvm_opt0_orc ; 
 int /*<<< orphan*/ * llvm_opt3_orc ; 

__attribute__((used)) static void
llvm_shutdown(int code, Datum arg)
{
	/* unregister profiling support, needs to be flushed to be useful */

	if (llvm_opt3_orc)
	{
#if defined(HAVE_DECL_LLVMORCREGISTERPERF) && HAVE_DECL_LLVMORCREGISTERPERF
		if (jit_profiling_support)
			LLVMOrcUnregisterPerf(llvm_opt3_orc);
#endif
		LLVMOrcDisposeInstance(llvm_opt3_orc);
		llvm_opt3_orc = NULL;
	}

	if (llvm_opt0_orc)
	{
#if defined(HAVE_DECL_LLVMORCREGISTERPERF) && HAVE_DECL_LLVMORCREGISTERPERF
		if (jit_profiling_support)
			LLVMOrcUnregisterPerf(llvm_opt0_orc);
#endif
		LLVMOrcDisposeInstance(llvm_opt0_orc);
		llvm_opt0_orc = NULL;
	}
}