#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_11__ {TYPE_2__* code; TYPE_4__* parser; int /*<<< orphan*/  heap; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ compiler_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  global_code; int /*<<< orphan*/  source; } ;
typedef  TYPE_2__ bytecode_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  compile_arguments (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  compile_function (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_pool_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_code (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  parser_release (TYPE_4__*) ; 
 int /*<<< orphan*/  release_bytecode (TYPE_2__*) ; 
 int /*<<< orphan*/  script_parse (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,TYPE_4__**) ; 

HRESULT compile_script(script_ctx_t *ctx, const WCHAR *code, const WCHAR *args, const WCHAR *delimiter,
        BOOL from_eval, BOOL use_decode, bytecode_t **ret)
{
    compiler_ctx_t compiler = {0};
    HRESULT hres;

    hres = init_code(&compiler, code);
    if(FAILED(hres))
        return hres;

    if(args) {
        hres = compile_arguments(&compiler, args);
        if(FAILED(hres))
            return hres;
    }

    if(use_decode) {
        hres = decode_source(compiler.code->source);
        if(FAILED(hres)) {
            WARN("Decoding failed\n");
            return hres;
        }
    }

    hres = script_parse(ctx, &compiler, compiler.code->source, delimiter, from_eval, &compiler.parser);
    if(FAILED(hres)) {
        release_bytecode(compiler.code);
        return hres;
    }

    heap_pool_init(&compiler.heap);
    hres = compile_function(&compiler, compiler.parser->source, NULL, from_eval, &compiler.code->global_code);
    heap_pool_free(&compiler.heap);
    parser_release(compiler.parser);
    if(FAILED(hres)) {
        release_bytecode(compiler.code);
        return hres;
    }

    *ret = compiler.code;
    return S_OK;
}