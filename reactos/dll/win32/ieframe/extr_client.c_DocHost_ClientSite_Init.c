#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {TYPE_2__ IServiceProvider_iface; TYPE_1__ IDispatch_iface; TYPE_6__ IOleControlSite_iface; TYPE_5__ IOleDocumentSite_iface; TYPE_4__ IOleInPlaceSiteEx_iface; TYPE_3__ IOleClientSite_iface; } ;
typedef  TYPE_7__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchVtbl ; 
 int /*<<< orphan*/  OleClientSiteVtbl ; 
 int /*<<< orphan*/  OleControlSiteVtbl ; 
 int /*<<< orphan*/  OleDocumentSiteVtbl ; 
 int /*<<< orphan*/  OleInPlaceSiteExVtbl ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 

void DocHost_ClientSite_Init(DocHost *This)
{
    This->IOleClientSite_iface.lpVtbl    = &OleClientSiteVtbl;
    This->IOleInPlaceSiteEx_iface.lpVtbl = &OleInPlaceSiteExVtbl;
    This->IOleDocumentSite_iface.lpVtbl  = &OleDocumentSiteVtbl;
    This->IOleControlSite_iface.lpVtbl   = &OleControlSiteVtbl;
    This->IDispatch_iface.lpVtbl         = &DispatchVtbl;
    This->IServiceProvider_iface.lpVtbl  = &ServiceProviderVtbl;
}