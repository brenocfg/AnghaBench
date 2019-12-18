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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_top (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_carray_set(script_ctx_t *ctx)
{
    const unsigned index = get_op_uint(ctx, 0);
    jsval_t value, array;
    HRESULT hres;

    value = stack_pop(ctx);

    TRACE("[%u] = %s\n", index, debugstr_jsval(value));

    array = stack_top(ctx);
    assert(is_object_instance(array));

    hres = jsdisp_propput_idx(iface_to_jsdisp(get_object(array)), index, value);
    jsval_release(value);
    return hres;
}