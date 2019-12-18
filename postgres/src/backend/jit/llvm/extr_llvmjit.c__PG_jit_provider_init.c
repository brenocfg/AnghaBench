#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  compile_expr; int /*<<< orphan*/  release_context; int /*<<< orphan*/  reset_after_error; } ;
typedef  TYPE_1__ JitProviderCallbacks ;

/* Variables and functions */
 int /*<<< orphan*/  llvm_compile_expr ; 
 int /*<<< orphan*/  llvm_release_context ; 
 int /*<<< orphan*/  llvm_reset_after_error ; 

void
_PG_jit_provider_init(JitProviderCallbacks *cb)
{
	cb->reset_after_error = llvm_reset_after_error;
	cb->release_context = llvm_release_context;
	cb->compile_expr = llvm_compile_expr;
}