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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * impl; TYPE_2__ IConnectionPointContainer_iface; int /*<<< orphan*/  pns; int /*<<< orphan*/  wbe; int /*<<< orphan*/  wbe2; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ ConnectionPointContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainerVtbl ; 
 int /*<<< orphan*/  ConnectionPoint_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DIID_DWebBrowserEvents ; 
 int /*<<< orphan*/  DIID_DWebBrowserEvents2 ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 

void ConnectionPointContainer_Init(ConnectionPointContainer *This, IUnknown *impl)
{
    This->IConnectionPointContainer_iface.lpVtbl = &ConnectionPointContainerVtbl;

    ConnectionPoint_Create(&DIID_DWebBrowserEvents2, &This->wbe2, &This->IConnectionPointContainer_iface);
    ConnectionPoint_Create(&DIID_DWebBrowserEvents,  &This->wbe,  &This->IConnectionPointContainer_iface);
    ConnectionPoint_Create(&IID_IPropertyNotifySink, &This->pns,  &This->IConnectionPointContainer_iface);

    This->impl = impl;
}