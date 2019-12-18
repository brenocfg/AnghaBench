#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* call_ctx; } ;
typedef  TYPE_2__ script_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  scope; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  scope_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_pop_scope(script_ctx_t *ctx)
{
    TRACE("\n");

    scope_pop(&ctx->call_ctx->scope);
    return S_OK;
}