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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_op_str (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT interp_throw_type(script_ctx_t *ctx)
{
    const HRESULT hres = get_op_uint(ctx, 0);
    jsstr_t *str = get_op_str(ctx, 1);
    const WCHAR *ptr;

    TRACE("%08x %s\n", hres, debugstr_jsstr(str));

    ptr = jsstr_flatten(str);
    return ptr ? throw_type_error(ctx, hres, ptr) : E_OUTOFMEMORY;
}