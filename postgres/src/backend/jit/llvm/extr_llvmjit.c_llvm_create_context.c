#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  resowner; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
typedef  TYPE_2__ LLVMJitContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 TYPE_2__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeJIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberJIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  llvm_assert_in_fatal_section () ; 
 int /*<<< orphan*/  llvm_session_initialize () ; 

LLVMJitContext *
llvm_create_context(int jitFlags)
{
	LLVMJitContext *context;

	llvm_assert_in_fatal_section();

	llvm_session_initialize();

	ResourceOwnerEnlargeJIT(CurrentResourceOwner);

	context = MemoryContextAllocZero(TopMemoryContext,
									 sizeof(LLVMJitContext));
	context->base.flags = jitFlags;

	/* ensure cleanup */
	context->base.resowner = CurrentResourceOwner;
	ResourceOwnerRememberJIT(CurrentResourceOwner, PointerGetDatum(context));

	return context;
}