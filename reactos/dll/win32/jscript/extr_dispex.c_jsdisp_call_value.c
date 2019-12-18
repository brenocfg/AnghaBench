#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctx; TYPE_2__* builtin_info; } ;
typedef  TYPE_3__ jsdisp_t ;
typedef  int WORD ;
struct TYPE_7__ {int /*<<< orphan*/  (* invoke ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ value_prop; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DISPATCH_CONSTRUCT ; 
 int DISPATCH_JSCRIPT_INTERNAL_MASK ; 
 int DISPATCH_METHOD ; 
 int /*<<< orphan*/  Function_invoke (TYPE_3__*,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JSCLASS_FUNCTION ; 
 int /*<<< orphan*/  JS_E_FUNCTION_EXPECTED ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_class (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdisp_release (int /*<<< orphan*/ *) ; 

HRESULT jsdisp_call_value(jsdisp_t *jsfunc, IDispatch *jsthis, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    HRESULT hres;

    assert(!(flags & ~(DISPATCH_METHOD|DISPATCH_CONSTRUCT|DISPATCH_JSCRIPT_INTERNAL_MASK)));

    if(is_class(jsfunc, JSCLASS_FUNCTION)) {
        hres = Function_invoke(jsfunc, jsthis, flags, argc, argv, r);
    }else {
        vdisp_t vdisp;

        if(!jsfunc->builtin_info->value_prop.invoke) {
            WARN("Not a function\n");
            return throw_type_error(jsfunc->ctx, JS_E_FUNCTION_EXPECTED, NULL);
        }

        set_disp(&vdisp, jsthis);
        flags &= ~DISPATCH_JSCRIPT_INTERNAL_MASK;
        hres = jsfunc->builtin_info->value_prop.invoke(jsfunc->ctx, &vdisp, flags, argc, argv, r);
        vdisp_release(&vdisp);
    }
    return hres;
}