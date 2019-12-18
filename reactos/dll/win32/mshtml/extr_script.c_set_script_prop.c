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
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  script; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int /*<<< orphan*/  IActiveScriptProperty ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptProperty_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptProperty_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IActiveScriptProperty ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void set_script_prop(ScriptHost *script_host, DWORD property, VARIANT *val)
{
    IActiveScriptProperty *script_prop;
    HRESULT hres;

    hres = IActiveScript_QueryInterface(script_host->script, &IID_IActiveScriptProperty,
            (void**)&script_prop);
    if(FAILED(hres)) {
        WARN("Could not get IActiveScriptProperty iface: %08x\n", hres);
        return;
    }

    hres = IActiveScriptProperty_SetProperty(script_prop, property, NULL, val);
    IActiveScriptProperty_Release(script_prop);
    if(FAILED(hres))
        WARN("SetProperty(%x) failed: %08x\n", property, hres);
}