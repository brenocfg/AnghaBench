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
struct TYPE_3__ {int script_state; int /*<<< orphan*/ * script; int /*<<< orphan*/ * parse; int /*<<< orphan*/ * parse_proc; } ;
typedef  TYPE_1__ ScriptHost ;

/* Variables and functions */
 int /*<<< orphan*/  IActiveScriptParseProcedure2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScriptParse_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IActiveScript_SetScriptState (int /*<<< orphan*/ *,int) ; 
#define  SCRIPTSTATE_CONNECTED 131 
#define  SCRIPTSTATE_DISCONNECTED 130 
#define  SCRIPTSTATE_INITIALIZED 129 
#define  SCRIPTSTATE_STARTED 128 
 int SCRIPTSTATE_UNINITIALIZED ; 

__attribute__((used)) static void release_script_engine(ScriptHost *This)
{
    if(!This->script)
        return;

    switch(This->script_state) {
    case SCRIPTSTATE_CONNECTED:
        IActiveScript_SetScriptState(This->script, SCRIPTSTATE_DISCONNECTED);

    case SCRIPTSTATE_STARTED:
    case SCRIPTSTATE_DISCONNECTED:
    case SCRIPTSTATE_INITIALIZED:
        IActiveScript_Close(This->script);

    default:
        if(This->parse_proc) {
            IActiveScriptParseProcedure2_Release(This->parse_proc);
            This->parse_proc = NULL;
        }

        if(This->parse) {
            IActiveScriptParse_Release(This->parse);
            This->parse = NULL;
        }
    }

    IActiveScript_Release(This->script);
    This->script = NULL;
    This->script_state = SCRIPTSTATE_UNINITIALIZED;
}