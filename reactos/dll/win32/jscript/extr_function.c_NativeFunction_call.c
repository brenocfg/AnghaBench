#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_5__ {int /*<<< orphan*/  global; int /*<<< orphan*/ * host_global; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* proc ) (TYPE_1__*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ NativeFunction ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 unsigned int DISPATCH_JSCRIPT_INTERNAL_MASK ; 
 int /*<<< orphan*/  set_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_jsdisp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdisp_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT NativeFunction_call(script_ctx_t *ctx, FunctionInstance *func, IDispatch *this_disp, unsigned flags,
        unsigned argc, jsval_t *argv, jsval_t *r)
{
    NativeFunction *function = (NativeFunction*)func;
    vdisp_t vthis;
    HRESULT hres;

    if(this_disp)
        set_disp(&vthis, this_disp);
    else if(ctx->host_global)
        set_disp(&vthis, ctx->host_global);
    else
        set_jsdisp(&vthis, ctx->global);

    hres = function->proc(ctx, &vthis, flags & ~DISPATCH_JSCRIPT_INTERNAL_MASK, argc, argv, r);

    vdisp_release(&vthis);
    return hres;
}