#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t sinks_size; TYPE_1__* sinks; } ;
struct TYPE_4__ {scalar_t__ propnotif; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  ConnectionPointContainer ;
typedef  TYPE_2__ ConnectionPoint ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  IPropertyNotifySink_OnChanged (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_cp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void call_property_onchanged(ConnectionPointContainer *container, DISPID dispid)
{
    ConnectionPoint *cp;
    DWORD i;

    cp = get_cp(container, &IID_IPropertyNotifySink, FALSE);
    if(!cp)
        return;

    for(i=0; i<cp->sinks_size; i++) {
        if(cp->sinks[i].propnotif)
            IPropertyNotifySink_OnChanged(cp->sinks[i].propnotif, dispid);
    }
}