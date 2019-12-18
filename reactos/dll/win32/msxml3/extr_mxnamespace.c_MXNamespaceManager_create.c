#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nscontext {int /*<<< orphan*/  entry; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_2__ IMXNamespaceManager_iface; int /*<<< orphan*/  override; int /*<<< orphan*/  ctxts; TYPE_1__ IVBMXNamespaceManager_iface; int /*<<< orphan*/  dispex; } ;
typedef  TYPE_3__ namespacemanager ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  MXNamespaceManagerVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  VBMXNamespaceManagerVtbl ; 
 struct nscontext* alloc_ns_context () ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namespacemanager_dispex ; 

HRESULT MXNamespaceManager_create(void **obj)
{
    namespacemanager *This;
    struct nscontext *ctxt;

    TRACE("(%p)\n", obj);

    This = heap_alloc( sizeof (*This) );
    if( !This )
        return E_OUTOFMEMORY;

    This->IMXNamespaceManager_iface.lpVtbl = &MXNamespaceManagerVtbl;
    This->IVBMXNamespaceManager_iface.lpVtbl = &VBMXNamespaceManagerVtbl;
    This->ref = 1;
    init_dispex(&This->dispex, (IUnknown*)&This->IVBMXNamespaceManager_iface, &namespacemanager_dispex);

    list_init(&This->ctxts);
    ctxt = alloc_ns_context();
    if (!ctxt)
    {
        heap_free(This);
        return E_OUTOFMEMORY;
    }

    list_add_head(&This->ctxts, &ctxt->entry);

    This->override = VARIANT_TRUE;

    *obj = &This->IMXNamespaceManager_iface;

    TRACE("returning iface %p\n", *obj);

    return S_OK;
}