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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  JS_E_OBJECT_REQUIRED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * get_object (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT stack_pop_object(script_ctx_t *ctx, IDispatch **r)
{
    jsval_t v;
    HRESULT hres;

    v = stack_pop(ctx);
    if(is_object_instance(v)) {
        if(!get_object(v))
            return throw_type_error(ctx, JS_E_OBJECT_REQUIRED, NULL);
        *r = get_object(v);
        return S_OK;
    }

    hres = to_object(ctx, v, r);
    jsval_release(v);
    return hres;
}