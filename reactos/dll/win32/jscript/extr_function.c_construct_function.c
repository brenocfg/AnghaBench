#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  function_endW ;
typedef  int /*<<< orphan*/  function_beginW ;
typedef  int /*<<< orphan*/  function_anonymousW ;
struct TYPE_6__ {int func_cnt; int var_cnt; int /*<<< orphan*/  funcs; } ;
struct TYPE_7__ {TYPE_1__ global_code; } ;
typedef  TYPE_2__ bytecode_t ;
typedef  float WCHAR ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ARRAY_SIZE (float const*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_script (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  create_source_function (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_w (float*) ; 
 void* heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  heap_free (float*) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int) ; 
 int /*<<< orphan*/  release_bytecode (TYPE_2__*) ; 
 int /*<<< orphan*/ * to_disp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT construct_function(script_ctx_t *ctx, unsigned argc, jsval_t *argv, IDispatch **ret)
{
    WCHAR *str = NULL, *ptr;
    unsigned len = 0, i = 0;
    bytecode_t *code;
    jsdisp_t *function;
    jsstr_t **params = NULL;
    int j = 0;
    HRESULT hres = S_OK;

    static const WCHAR function_anonymousW[] = {'f','u','n','c','t','i','o','n',' ','a','n','o','n','y','m','o','u','s','('};
    static const WCHAR function_beginW[] = {')',' ','{','\n'};
    static const WCHAR function_endW[] = {'\n','}',0};

    if(argc) {
        params = heap_alloc(argc*sizeof(*params));
        if(!params)
            return E_OUTOFMEMORY;

        if(argc > 2)
            len = (argc-2)*2; /* separating commas */
        for(i=0; i < argc; i++) {
            hres = to_string(ctx, argv[i], params+i);
            if(FAILED(hres))
                break;
            len += jsstr_length(params[i]);
        }
    }

    if(SUCCEEDED(hres)) {
        len += ARRAY_SIZE(function_anonymousW) + ARRAY_SIZE(function_beginW) + ARRAY_SIZE(function_endW);
        str = heap_alloc(len*sizeof(WCHAR));
        if(str) {
            memcpy(str, function_anonymousW, sizeof(function_anonymousW));
            ptr = str + ARRAY_SIZE(function_anonymousW);
            if(argc > 1) {
                while(1) {
                    ptr += jsstr_flush(params[j], ptr);
                    if(++j == argc-1)
                        break;
                    *ptr++ = ',';
                    *ptr++ = ' ';
                }
            }
            memcpy(ptr, function_beginW, sizeof(function_beginW));
            ptr += ARRAY_SIZE(function_beginW);
            if(argc)
                ptr += jsstr_flush(params[argc-1], ptr);
            memcpy(ptr, function_endW, sizeof(function_endW));

            TRACE("%s\n", debugstr_w(str));
        }else {
            hres = E_OUTOFMEMORY;
        }
    }

    while(i)
        jsstr_release(params[--i]);
    heap_free(params);
    if(FAILED(hres))
        return hres;

    hres = compile_script(ctx, str, NULL, NULL, FALSE, FALSE, &code);
    heap_free(str);
    if(FAILED(hres))
        return hres;

    if(code->global_code.func_cnt != 1 || code->global_code.var_cnt != 1) {
        ERR("Invalid parser result!\n");
        release_bytecode(code);
        return E_UNEXPECTED;
    }

    hres = create_source_function(ctx, code, code->global_code.funcs, NULL, &function);
    release_bytecode(code);
    if(FAILED(hres))
        return hres;

    *ret = to_disp(function);
    return S_OK;
}