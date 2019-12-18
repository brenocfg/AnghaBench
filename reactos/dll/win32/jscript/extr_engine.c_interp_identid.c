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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_op_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  interp_identifier_ref (int /*<<< orphan*/ *,int /*<<< orphan*/  const,unsigned int const) ; 

__attribute__((used)) static HRESULT interp_identid(script_ctx_t *ctx)
{
    const BSTR arg = get_op_bstr(ctx, 0);
    const unsigned flags = get_op_uint(ctx, 1);

    TRACE("%s %x\n", debugstr_w(arg), flags);

    return interp_identifier_ref(ctx, arg, flags);
}