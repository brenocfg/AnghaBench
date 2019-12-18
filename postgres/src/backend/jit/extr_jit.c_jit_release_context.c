#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* release_context ) (TYPE_1__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  resowner; } ;
typedef  TYPE_1__ JitContext ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  ResourceOwnerForgetJIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 TYPE_3__ provider ; 
 scalar_t__ provider_successfully_loaded ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
jit_release_context(JitContext *context)
{
	if (provider_successfully_loaded)
		provider.release_context(context);

	ResourceOwnerForgetJIT(context->resowner, PointerGetDatum(context));
	pfree(context);
}