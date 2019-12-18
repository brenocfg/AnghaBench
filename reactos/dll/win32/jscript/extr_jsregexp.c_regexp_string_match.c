#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  tmp_heap; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  match_state_t ;
struct TYPE_15__ {scalar_t__ length; scalar_t__ index; } ;
typedef  TYPE_2__ match_result_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  heap_pool_t ;
typedef  char WCHAR ;
struct TYPE_16__ {int /*<<< orphan*/  dispex; TYPE_12__* jsregexp; } ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_3__ RegExpInstance ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int REG_GLOB ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * alloc_match_state (TYPE_12__*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ create_array (TYPE_1__*,unsigned int,int /*<<< orphan*/ **) ; 
 scalar_t__ create_match_array (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_pool_mark (int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_propput_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_propput_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 char* jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_number (scalar_t__) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 TYPE_3__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 
 scalar_t__ regexp_match (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,unsigned int*) ; 
 scalar_t__ regexp_match_next (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT regexp_string_match(script_ctx_t *ctx, jsdisp_t *re, jsstr_t *jsstr, jsval_t *r)
{
    static const WCHAR indexW[] = {'i','n','d','e','x',0};
    static const WCHAR inputW[] = {'i','n','p','u','t',0};
    static const WCHAR lastIndexW[] = {'l','a','s','t','I','n','d','e','x',0};

    RegExpInstance *regexp = regexp_from_jsdisp(re);
    match_result_t *match_result;
    unsigned match_cnt, i;
    const WCHAR *str;
    jsdisp_t *array;
    HRESULT hres;

    str = jsstr_flatten(jsstr);
    if(!str)
        return E_OUTOFMEMORY;

    if(!(regexp->jsregexp->flags & REG_GLOB)) {
        match_state_t *match;
        heap_pool_t *mark;

        mark = heap_pool_mark(&ctx->tmp_heap);
        match = alloc_match_state(regexp->jsregexp, &ctx->tmp_heap, str);
        if(!match) {
            heap_pool_clear(mark);
            return E_OUTOFMEMORY;
        }

        hres = regexp_match_next(ctx, &regexp->dispex, 0, jsstr, &match);
        if(FAILED(hres)) {
            heap_pool_clear(mark);
            return hres;
        }

        if(r) {
            if(hres == S_OK) {
                IDispatch *ret;

                hres = create_match_array(ctx, jsstr, match, &ret);
                if(SUCCEEDED(hres))
                    *r = jsval_disp(ret);
            }else {
                *r = jsval_null();
            }
        }

        heap_pool_clear(mark);
        return S_OK;
    }

    hres = regexp_match(ctx, &regexp->dispex, jsstr, FALSE, &match_result, &match_cnt);
    if(FAILED(hres))
        return hres;

    if(!match_cnt) {
        TRACE("no match\n");

        if(r)
            *r = jsval_null();
        return S_OK;
    }

    hres = create_array(ctx, match_cnt, &array);
    if(FAILED(hres))
        return hres;

    for(i=0; i < match_cnt; i++) {
        jsstr_t *tmp_str;

        tmp_str = jsstr_substr(jsstr, match_result[i].index, match_result[i].length);
        if(!tmp_str) {
            hres = E_OUTOFMEMORY;
            break;
        }

        hres = jsdisp_propput_idx(array, i, jsval_string(tmp_str));
        jsstr_release(tmp_str);
        if(FAILED(hres))
            break;
    }

    while(SUCCEEDED(hres)) {
        hres = jsdisp_propput_name(array, indexW, jsval_number(match_result[match_cnt-1].index));
        if(FAILED(hres))
            break;

        hres = jsdisp_propput_name(array, lastIndexW,
                jsval_number(match_result[match_cnt-1].index + match_result[match_cnt-1].length));
        if(FAILED(hres))
            break;

        hres = jsdisp_propput_name(array, inputW, jsval_string(jsstr));
        break;
    }

    heap_free(match_result);

    if(SUCCEEDED(hres) && r)
        *r = jsval_obj(array);
    else
        jsdisp_release(array);
    return hres;
}