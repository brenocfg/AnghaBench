#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  global_code; } ;
typedef  TYPE_1__ bytecode_t ;
struct TYPE_10__ {int /*<<< orphan*/  global; } ;
struct TYPE_9__ {int /*<<< orphan*/  site; TYPE_3__* ctx; } ;
typedef  TYPE_2__ JScript ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_GLOBAL ; 
 int /*<<< orphan*/  IActiveScriptSite_OnEnterScript (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptSite_OnLeaveScript (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ei (TYPE_3__*) ; 
 int /*<<< orphan*/  exec_source (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exec_global_code(JScript *This, bytecode_t *code)
{
    HRESULT hres;

    IActiveScriptSite_OnEnterScript(This->site);

    clear_ei(This->ctx);
    hres = exec_source(This->ctx, EXEC_GLOBAL, code, &code->global_code, NULL, NULL, NULL, This->ctx->global, 0, NULL, NULL);

    IActiveScriptSite_OnLeaveScript(This->site);
    return hres;
}