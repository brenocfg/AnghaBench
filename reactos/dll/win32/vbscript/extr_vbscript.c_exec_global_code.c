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
struct TYPE_6__ {int /*<<< orphan*/  main_code; int /*<<< orphan*/  pending_exec; } ;
typedef  TYPE_1__ vbscode_t ;
struct TYPE_7__ {int /*<<< orphan*/  site; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IActiveScriptSite_OnEnterScript (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptSite_OnLeaveScript (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_script (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exec_global_code(script_ctx_t *ctx, vbscode_t *code)
{
    HRESULT hres;

    code->pending_exec = FALSE;

    IActiveScriptSite_OnEnterScript(ctx->site);
    hres = exec_script(ctx, &code->main_code, NULL, NULL, NULL);
    IActiveScriptSite_OnLeaveScript(ctx->site);

    return hres;
}