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
typedef  int /*<<< orphan*/  exprval_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  exprval_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprval_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop_exprval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  typeof_string (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  const* unknownW ; 

__attribute__((used)) static HRESULT interp_typeofid(script_ctx_t *ctx)
{
    const WCHAR *ret;
    exprval_t ref;
    jsval_t v;
    HRESULT hres;

    TRACE("\n");

    if(!stack_pop_exprval(ctx, &ref))
        return stack_push(ctx, jsval_string(jsstr_undefined()));

    hres = exprval_propget(ctx, &ref, &v);
    exprval_release(&ref);
    if(FAILED(hres))
        return stack_push_string(ctx, unknownW);

    hres = typeof_string(v, &ret);
    jsval_release(v);
    if(FAILED(hres))
        return hres;

    return stack_push_string(ctx, ret);
}