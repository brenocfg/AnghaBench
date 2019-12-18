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
struct TYPE_3__ {scalar_t__ state; scalar_t__ site; } ;
typedef  TYPE_1__ VBScript ;
typedef  scalar_t__ SCRIPTSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  IActiveScriptSite_OnStateChange (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void change_state(VBScript *This, SCRIPTSTATE state)
{
    if(This->state == state)
        return;

    This->state = state;
    if(This->site)
        IActiveScriptSite_OnStateChange(This->site, state);
}