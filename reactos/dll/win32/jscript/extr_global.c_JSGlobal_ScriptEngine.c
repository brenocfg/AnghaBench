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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * jsstr_alloc (char const*) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT JSGlobal_ScriptEngine(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    static const WCHAR JScriptW[] = {'J','S','c','r','i','p','t',0};

    TRACE("\n");

    if(r) {
        jsstr_t *ret;

        ret = jsstr_alloc(JScriptW);
        if(!ret)
            return E_OUTOFMEMORY;

        *r = jsval_string(ret);
    }

    return S_OK;
}