#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_10__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_15__ {TYPE_1__ node; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {TYPE_6__ element; int /*<<< orphan*/  nstable; TYPE_4__ IHTMLTable3_iface; TYPE_3__ IHTMLTable2_iface; TYPE_2__ IHTMLTable_iface; } ;
typedef  TYPE_5__ HTMLTable ;
typedef  TYPE_6__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLElement_Init (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLTable2Vtbl ; 
 int /*<<< orphan*/  HTMLTable3Vtbl ; 
 int /*<<< orphan*/  HTMLTableImplVtbl ; 
 int /*<<< orphan*/  HTMLTableVtbl ; 
 int /*<<< orphan*/  HTMLTable_dispex ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLTableElement ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* heap_alloc_zero (int) ; 
 scalar_t__ nsIDOMHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

HRESULT HTMLTable_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLTable *ret;
    nsresult nsres;

    ret = heap_alloc_zero(sizeof(HTMLTable));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->element.node.vtbl = &HTMLTableImplVtbl;
    ret->IHTMLTable_iface.lpVtbl = &HTMLTableVtbl;
    ret->IHTMLTable2_iface.lpVtbl = &HTMLTable2Vtbl;
    ret->IHTMLTable3_iface.lpVtbl = &HTMLTable3Vtbl;

    HTMLElement_Init(&ret->element, doc, nselem, &HTMLTable_dispex);

    nsres = nsIDOMHTMLElement_QueryInterface(nselem, &IID_nsIDOMHTMLTableElement, (void**)&ret->nstable);
    assert(nsres == NS_OK);

    *elem = &ret->element;
    return S_OK;
}