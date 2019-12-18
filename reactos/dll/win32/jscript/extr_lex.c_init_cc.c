#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* script; } ;
typedef  TYPE_2__ parser_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/ * vars; } ;
typedef  TYPE_3__ cc_ctx_t ;
struct TYPE_9__ {TYPE_3__* cc; } ;
typedef  double DOUBLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ JSCRIPT_BUILD_VERSION ; 
 scalar_t__ JSCRIPT_MAJOR_VERSION ; 
 scalar_t__ JSCRIPT_MINOR_VERSION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ccval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccval_num (scalar_t__) ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  lex_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_cc_var (TYPE_3__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_cc (TYPE_3__*) ; 

__attribute__((used)) static BOOL init_cc(parser_ctx_t *ctx)
{
    cc_ctx_t *cc;

    if(ctx->script->cc)
        return TRUE;

    cc = heap_alloc(sizeof(cc_ctx_t));
    if(!cc) {
        lex_error(ctx, E_OUTOFMEMORY);
        return FALSE;
    }

    cc->vars = NULL;

    if(!new_cc_var(cc, L"_jscript", -1, ccval_bool(TRUE))
       || !new_cc_var(cc, sizeof(void*) == 8 ? L"_win64" : L"_win32", -1, ccval_bool(TRUE))
       || !new_cc_var(cc, sizeof(void*) == 8 ? L"_amd64" : L"_x86", -1, ccval_bool(TRUE))
       || !new_cc_var(cc, L"_jscript_version", -1, ccval_num(JSCRIPT_MAJOR_VERSION + (DOUBLE)JSCRIPT_MINOR_VERSION/10.0))
       || !new_cc_var(cc, L"_jscript_build", -1, ccval_num(JSCRIPT_BUILD_VERSION))) {
        release_cc(cc);
        lex_error(ctx, E_OUTOFMEMORY);
        return FALSE;
    }

    ctx->script->cc = cc;
    return TRUE;
}