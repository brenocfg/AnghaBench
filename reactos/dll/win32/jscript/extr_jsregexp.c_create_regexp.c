#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tmp_heap; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  dispex; int /*<<< orphan*/  jsregexp; int /*<<< orphan*/ * str; int /*<<< orphan*/  last_index_val; } ;
typedef  TYPE_2__ RegExpInstance ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  alloc_regexp (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regexp_new (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT create_regexp(script_ctx_t *ctx, jsstr_t *src, DWORD flags, jsdisp_t **ret)
{
    RegExpInstance *regexp;
    const WCHAR *str;
    HRESULT hres;

    str = jsstr_flatten(src);
    if(!str)
        return E_OUTOFMEMORY;

    TRACE("%s %x\n", debugstr_wn(str, jsstr_length(src)), flags);

    hres = alloc_regexp(ctx, NULL, &regexp);
    if(FAILED(hres))
        return hres;

    regexp->str = jsstr_addref(src);
    regexp->last_index_val = jsval_number(0);

    regexp->jsregexp = regexp_new(ctx, &ctx->tmp_heap, str, jsstr_length(regexp->str), flags, FALSE);
    if(!regexp->jsregexp) {
        WARN("regexp_new failed\n");
        jsdisp_release(&regexp->dispex);
        return E_FAIL;
    }

    *ret = &regexp->dispex;
    return S_OK;
}