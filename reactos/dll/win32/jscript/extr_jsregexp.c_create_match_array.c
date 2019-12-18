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
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_5__ {size_t paren_count; char const* cp; int match_len; TYPE_1__* parens; } ;
typedef  TYPE_2__ match_state_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  char WCHAR ;
struct TYPE_4__ {int index; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (char const*,int) ; 
 int /*<<< orphan*/ * jsstr_empty () ; 
 char* jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_disp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_match_array(script_ctx_t *ctx, jsstr_t *input_str,
        const match_state_t *result, IDispatch **ret)
{
    const WCHAR *input;
    jsdisp_t *array;
    jsstr_t *str;
    DWORD i;
    HRESULT hres = S_OK;

    static const WCHAR indexW[] = {'i','n','d','e','x',0};
    static const WCHAR inputW[] = {'i','n','p','u','t',0};
    static const WCHAR lastIndexW[] = {'l','a','s','t','I','n','d','e','x',0};
    static const WCHAR zeroW[] = {'0',0};

    input = jsstr_flatten(input_str);
    if(!input)
        return E_OUTOFMEMORY;

    hres = create_array(ctx, result->paren_count+1, &array);
    if(FAILED(hres))
        return hres;

    for(i=0; i < result->paren_count; i++) {
        if(result->parens[i].index != -1)
            str = jsstr_substr(input_str, result->parens[i].index, result->parens[i].length);
        else
            str = jsstr_empty();
        if(!str) {
            hres = E_OUTOFMEMORY;
            break;
        }

        hres = jsdisp_propput_idx(array, i+1, jsval_string(str));
        jsstr_release(str);
        if(FAILED(hres))
            break;
    }

    while(SUCCEEDED(hres)) {
        hres = jsdisp_propput_name(array, indexW, jsval_number(result->cp-input-result->match_len));
        if(FAILED(hres))
            break;

        hres = jsdisp_propput_name(array, lastIndexW, jsval_number(result->cp-input));
        if(FAILED(hres))
            break;

        hres = jsdisp_propput_name(array, inputW, jsval_string(jsstr_addref(input_str)));
        if(FAILED(hres))
            break;

        str = jsstr_alloc_len(result->cp-result->match_len, result->match_len);
        if(!str) {
            hres = E_OUTOFMEMORY;
            break;
        }
        hres = jsdisp_propput_name(array, zeroW, jsval_string(str));
        jsstr_release(str);
        break;
    }

    if(FAILED(hres)) {
        jsdisp_release(array);
        return hres;
    }

    *ret = to_disp(array);
    return S_OK;
}