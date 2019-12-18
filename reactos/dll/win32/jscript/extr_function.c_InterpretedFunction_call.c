#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_9__ {int /*<<< orphan*/  dispex; } ;
struct TYPE_11__ {TYPE_1__ function; int /*<<< orphan*/  scope_chain; int /*<<< orphan*/  func_code; int /*<<< orphan*/  code; } ;
typedef  TYPE_3__ InterpretedFunction ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int DISPATCH_CONSTRUCT ; 
 unsigned int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int /*<<< orphan*/  EXEC_CONSTRUCTOR ; 
 int /*<<< orphan*/  EXEC_RETURN_TO_INTERP ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SCRIPTSTATE_CLOSED ; 
 scalar_t__ SCRIPTSTATE_UNINITIALIZED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  create_dispex (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_object (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  exec_source (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_disp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT InterpretedFunction_call(script_ctx_t *ctx, FunctionInstance *func, IDispatch *this_obj, unsigned flags,
         unsigned argc, jsval_t *argv, jsval_t *r)
{
    InterpretedFunction *function = (InterpretedFunction*)func;
    jsdisp_t *var_disp, *new_obj = NULL;
    DWORD exec_flags = 0;
    HRESULT hres;

    TRACE("%p\n", function);

    if(ctx->state == SCRIPTSTATE_UNINITIALIZED || ctx->state == SCRIPTSTATE_CLOSED) {
        WARN("Script engine state does not allow running code.\n");
        return E_UNEXPECTED;
    }

    if(flags & DISPATCH_CONSTRUCT) {
        hres = create_object(ctx, &function->function.dispex, &new_obj);
        if(FAILED(hres))
            return hres;
        this_obj = to_disp(new_obj);
    }

    if(flags & DISPATCH_JSCRIPT_CALLEREXECSSOURCE)
        exec_flags |= EXEC_RETURN_TO_INTERP;
    if(flags & DISPATCH_CONSTRUCT)
        exec_flags |= EXEC_CONSTRUCTOR;

    hres = create_dispex(ctx, NULL, NULL, &var_disp);
    if(SUCCEEDED(hres))
        hres = exec_source(ctx, exec_flags, function->code, function->func_code, function->scope_chain, this_obj,
                           &function->function.dispex, var_disp, argc, argv, r);
    if(new_obj)
        jsdisp_release(new_obj);

    jsdisp_release(var_disp);
    return hres;
}