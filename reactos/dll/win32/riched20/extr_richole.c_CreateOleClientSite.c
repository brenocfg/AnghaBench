#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/  entry; TYPE_3__* reole; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int ref; TYPE_5__ IOleClientSite_iface; TYPE_1__ child; TYPE_2__ IOleInPlaceSite_iface; } ;
struct TYPE_11__ {int /*<<< orphan*/  clientsites; } ;
typedef  TYPE_3__ IRichEditOleImpl ;
typedef  TYPE_4__ IOleClientSiteImpl ;
typedef  TYPE_5__ IOleClientSite ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_4__* heap_alloc (int) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocst ; 
 int /*<<< orphan*/  olestvt ; 

__attribute__((used)) static HRESULT CreateOleClientSite(IRichEditOleImpl *reOle, IOleClientSite **ret)
{
    IOleClientSiteImpl *clientSite = heap_alloc(sizeof *clientSite);

    if (!clientSite)
        return E_OUTOFMEMORY;

    clientSite->IOleClientSite_iface.lpVtbl = &ocst;
    clientSite->IOleInPlaceSite_iface.lpVtbl = &olestvt;
    clientSite->ref = 1;
    clientSite->child.reole = reOle;
    list_add_head(&reOle->clientsites, &clientSite->child.entry);

    *ret = &clientSite->IOleClientSite_iface;
    return S_OK;
}