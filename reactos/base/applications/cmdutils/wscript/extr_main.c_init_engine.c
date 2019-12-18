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
typedef  int /*<<< orphan*/  IActiveScriptParse ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IActiveScriptParse_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_AddNamedItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScript_SetScriptSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTITEM_ISVISIBLE ; 
 int /*<<< orphan*/  SCRIPTSTATE_INITIALIZED ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_typelib () ; 
 int /*<<< orphan*/  script_site ; 
 int /*<<< orphan*/  wscriptW ; 
 int /*<<< orphan*/  wshW ; 

__attribute__((used)) static BOOL init_engine(IActiveScript *script, IActiveScriptParse *parser)
{
    HRESULT hres;

    if(!load_typelib())
        return FALSE;

    hres = IActiveScript_SetScriptSite(script, &script_site);
    if(FAILED(hres))
        return FALSE;

    hres = IActiveScriptParse_InitNew(parser);
    if(FAILED(hres))
        return FALSE;

    hres = IActiveScript_AddNamedItem(script, wscriptW, SCRIPTITEM_ISVISIBLE);
    if(FAILED(hres))
        return FALSE;

    hres = IActiveScript_AddNamedItem(script, wshW, SCRIPTITEM_ISVISIBLE);
    if(FAILED(hres))
        return FALSE;

    hres = IActiveScript_SetScriptState(script, SCRIPTSTATE_INITIALIZED);
    return SUCCEEDED(hres);
}