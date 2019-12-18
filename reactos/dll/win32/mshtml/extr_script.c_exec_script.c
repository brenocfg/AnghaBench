#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ei ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  parse; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  EXCEPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CO_E_CLASSSTRING ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCRIPTTEXT_ISVISIBLE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  get_guid_from_language (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_script_host (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

HRESULT exec_script(HTMLInnerWindow *window, const WCHAR *code, const WCHAR *lang, VARIANT *ret)
{
    ScriptHost *script_host;
    EXCEPINFO ei;
    GUID guid;
    HRESULT hres;

    static const WCHAR delimW[] = {'"',0};

    if(!get_guid_from_language(lang, &guid)) {
        WARN("Could not find script GUID\n");
        return CO_E_CLASSSTRING;
    }

    script_host = get_script_host(window, &guid);
    if(!script_host) {
        FIXME("No script host\n");
        return E_FAIL;
    }

    if(!script_host->parse) {
        FIXME("script_host->parse == NULL\n");
        return E_FAIL;
    }

    memset(&ei, 0, sizeof(ei));
    TRACE(">>>\n");
    hres = IActiveScriptParse_ParseScriptText(script_host->parse, code, NULL, NULL, delimW, 0, 0, SCRIPTTEXT_ISVISIBLE, ret, &ei);
    if(SUCCEEDED(hres))
        TRACE("<<<\n");
    else
        WARN("<<< %08x\n", hres);

    return hres;
}