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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptParse_ParseScriptText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SCRIPTITEM_ISVISIBLE ; 
 int /*<<< orphan*/  SCRIPTSTATE_STARTED ; 
 int SCRIPTTEXT_HOSTMANAGESSOURCE ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_FIXME (char*,...) ; 
 int /*<<< orphan*/  get_script_str (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void run_script(const WCHAR *filename, IActiveScript *script, IActiveScriptParse *parser)
{
    BSTR text;
    HRESULT hres;

    text = get_script_str(filename);
    if(!text) {
        WINE_FIXME("Could not get script text\n");
        return;
    }

    hres = IActiveScriptParse_ParseScriptText(parser, text, NULL, NULL, NULL, 1, 1,
            SCRIPTTEXT_HOSTMANAGESSOURCE|SCRIPTITEM_ISVISIBLE, NULL, NULL);
    SysFreeString(text);
    if(FAILED(hres)) {
        WINE_FIXME("ParseScriptText failed: %08x\n", hres);
        return;
    }

    hres = IActiveScript_SetScriptState(script, SCRIPTSTATE_STARTED);
    if(FAILED(hres))
        WINE_FIXME("SetScriptState failed: %08x\n", hres);
}