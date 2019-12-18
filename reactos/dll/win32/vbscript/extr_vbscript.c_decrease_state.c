#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; int /*<<< orphan*/  thread_id; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * site; } ;
typedef  TYPE_1__ VBScript ;
typedef  int SCRIPTSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
 int /*<<< orphan*/  IActiveScriptSite_Release (int /*<<< orphan*/ *) ; 
#define  SCRIPTSTATE_CLOSED 133 
#define  SCRIPTSTATE_CONNECTED 132 
#define  SCRIPTSTATE_DISCONNECTED 131 
#define  SCRIPTSTATE_INITIALIZED 130 
#define  SCRIPTSTATE_STARTED 129 
#define  SCRIPTSTATE_UNINITIALIZED 128 
 int /*<<< orphan*/  change_state (TYPE_1__*,int) ; 
 int /*<<< orphan*/  release_script (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decrease_state(VBScript *This, SCRIPTSTATE state)
{
    switch(This->state) {
    case SCRIPTSTATE_CONNECTED:
        change_state(This, SCRIPTSTATE_DISCONNECTED);
        if(state == SCRIPTSTATE_DISCONNECTED)
            return;
        /* FALLTHROUGH */
    case SCRIPTSTATE_STARTED:
    case SCRIPTSTATE_DISCONNECTED:
        if(This->state == SCRIPTSTATE_DISCONNECTED)
            change_state(This, SCRIPTSTATE_INITIALIZED);
        if(state == SCRIPTSTATE_INITIALIZED)
            break;
        /* FALLTHROUGH */
    case SCRIPTSTATE_INITIALIZED:
    case SCRIPTSTATE_UNINITIALIZED:
        change_state(This, state);

        if(This->site) {
            IActiveScriptSite_Release(This->site);
            This->site = NULL;
        }

        if(This->ctx)
            release_script(This->ctx);

        This->thread_id = 0;
        break;
    case SCRIPTSTATE_CLOSED:
        break;
    DEFAULT_UNREACHABLE;
    }
}