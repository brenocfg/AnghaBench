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
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_op_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identifier_value (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static HRESULT interp_ident(script_ctx_t *ctx)
{
    const BSTR arg = get_op_bstr(ctx, 0);

    TRACE("%s\n", debugstr_w(arg));

    return identifier_value(ctx, arg);
}