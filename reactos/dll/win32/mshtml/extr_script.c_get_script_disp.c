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
struct TYPE_3__ {int /*<<< orphan*/  script; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScript_GetScriptDispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  windowW ; 

IDispatch *get_script_disp(ScriptHost *script_host)
{
    IDispatch *disp;
    HRESULT hres;

    if(!script_host->script)
        return NULL;

    hres = IActiveScript_GetScriptDispatch(script_host->script, windowW, &disp);
    if(FAILED(hres))
        return NULL;

    return disp;
}