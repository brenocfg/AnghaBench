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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const) ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ **) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_carray(script_ctx_t *ctx)
{
    const unsigned arg = get_op_uint(ctx, 0);
    jsdisp_t *array;
    HRESULT hres;

    TRACE("%u\n", arg);

    hres = create_array(ctx, arg, &array);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, jsval_obj(array));
}