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
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  compiler_alloc_bstr_len (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 scalar_t__ iswalnum (char const) ; 
 int /*<<< orphan*/  iswalpha (char const) ; 
 scalar_t__ iswspace (char const) ; 

__attribute__((used)) static HRESULT parse_arguments(compiler_ctx_t *ctx, const WCHAR *args, BSTR *arg_array, unsigned *args_size)
{
    const WCHAR *ptr = args, *ptr2;
    unsigned arg_cnt = 0;

    while(iswspace(*ptr))
        ptr++;
    if(!*ptr) {
        if(args_size)
            *args_size = 0;
        return S_OK;
    }

    while(1) {
        if(!iswalpha(*ptr) && *ptr != '_') {
            FIXME("expected alpha or '_': %s\n", debugstr_w(ptr));
            return E_FAIL;
        }

        ptr2 = ptr;
        while(iswalnum(*ptr) || *ptr == '_')
            ptr++;

        if(*ptr && *ptr != ',' && !iswspace(*ptr)) {
            FIXME("unexpected har %s\n", debugstr_w(ptr));
            return E_FAIL;
        }

        if(arg_array) {
            arg_array[arg_cnt] = compiler_alloc_bstr_len(ctx, ptr2, ptr-ptr2);
            if(!arg_array[arg_cnt])
                return E_OUTOFMEMORY;
        }
        arg_cnt++;

        while(iswspace(*ptr))
            ptr++;
        if(!*ptr)
            break;
        if(*ptr != ',') {
            FIXME("expected ',': %s\n", debugstr_w(ptr));
            return E_FAIL;
        }

        ptr++;
        while(iswspace(*ptr))
            ptr++;
    }

    if(args_size)
        *args_size = arg_cnt;
    return S_OK;
}