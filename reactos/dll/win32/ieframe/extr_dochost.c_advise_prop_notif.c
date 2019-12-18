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
struct TYPE_3__ {scalar_t__ is_prop_notif; int /*<<< orphan*/  prop_notif_cookie; int /*<<< orphan*/  IPropertyNotifySink_iface; int /*<<< orphan*/  document; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  int /*<<< orphan*/  IConnectionPoint ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DocHost ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IConnectionPointContainer_FindConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IConnectionPointContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Unadvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void advise_prop_notif(DocHost *This, BOOL set)
{
    IConnectionPointContainer *cp_container;
    IConnectionPoint *cp;
    HRESULT hres;

    hres = IUnknown_QueryInterface(This->document, &IID_IConnectionPointContainer, (void**)&cp_container);
    if(FAILED(hres))
        return;

    hres = IConnectionPointContainer_FindConnectionPoint(cp_container, &IID_IPropertyNotifySink, &cp);
    IConnectionPointContainer_Release(cp_container);
    if(FAILED(hres))
        return;

    if(set)
        hres = IConnectionPoint_Advise(cp, (IUnknown*)&This->IPropertyNotifySink_iface, &This->prop_notif_cookie);
    else
        hres = IConnectionPoint_Unadvise(cp, This->prop_notif_cookie);
    IConnectionPoint_Release(cp);

    if(SUCCEEDED(hres))
        This->is_prop_notif = set;
}