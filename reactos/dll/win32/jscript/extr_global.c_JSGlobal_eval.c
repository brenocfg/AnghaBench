#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_11__ {int /*<<< orphan*/  global; TYPE_2__* call_ctx; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  variable_obj; int /*<<< orphan*/ * this_obj; int /*<<< orphan*/ * scope; } ;
typedef  TYPE_2__ call_frame_t ;
struct TYPE_13__ {int /*<<< orphan*/  global_code; } ;
typedef  TYPE_3__ bytecode_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int EXEC_EVAL ; 
 int EXEC_GLOBAL ; 
 int EXEC_RETURN_TO_INTERP ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_script (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_source (TYPE_1__*,int,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  release_bytecode (TYPE_3__*) ; 
 int /*<<< orphan*/  throw_syntax_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT JSGlobal_eval(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    call_frame_t *frame = ctx->call_ctx;
    DWORD exec_flags = EXEC_EVAL;
    bytecode_t *code;
    const WCHAR *src;
    HRESULT hres;

    TRACE("\n");

    if(!argc) {
        if(r)
            *r = jsval_undefined();
        return S_OK;
    }

    if(!is_string(argv[0])) {
        if(r)
            return jsval_copy(argv[0], r);
        return S_OK;
    }

    src = jsstr_flatten(get_string(argv[0]));
    if(!src)
        return E_OUTOFMEMORY;

    TRACE("parsing %s\n", debugstr_jsval(argv[0]));
    hres = compile_script(ctx, src, NULL, NULL, TRUE, FALSE, &code);
    if(FAILED(hres)) {
        WARN("parse (%s) failed: %08x\n", debugstr_jsval(argv[0]), hres);
        return throw_syntax_error(ctx, hres, NULL);
    }

    if(!frame || (frame->flags & EXEC_GLOBAL))
        exec_flags |= EXEC_GLOBAL;
    if(flags & DISPATCH_JSCRIPT_CALLEREXECSSOURCE)
        exec_flags |= EXEC_RETURN_TO_INTERP;
    hres = exec_source(ctx, exec_flags, code, &code->global_code, frame ? frame->scope : NULL,
            frame ? frame->this_obj : NULL, NULL, frame ? frame->variable_obj : ctx->global, 0, NULL, r);
    release_bytecode(code);
    return hres;
}