#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* match_parens; int /*<<< orphan*/  last_match; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT global_idx(script_ctx_t *ctx, DWORD idx, jsval_t *r)
{
    jsstr_t *ret;

    ret = jsstr_substr(ctx->last_match, ctx->match_parens[idx].index, ctx->match_parens[idx].length);
    if(!ret)
        return E_OUTOFMEMORY;

    *r = jsval_string(ret);
    return S_OK;
}