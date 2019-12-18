#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMClientRect ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IHTMLRect_iface; int /*<<< orphan*/ * nsrect; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IHTMLRect ;
typedef  TYPE_2__ HTMLRect ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLRectVtbl ; 
 int /*<<< orphan*/  HTMLRect_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMClientRect_AddRef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_html_rect(nsIDOMClientRect *nsrect, IHTMLRect **ret)
{
    HTMLRect *rect;

    rect = heap_alloc_zero(sizeof(HTMLRect));
    if(!rect)
        return E_OUTOFMEMORY;

    rect->IHTMLRect_iface.lpVtbl = &HTMLRectVtbl;
    rect->ref = 1;

    init_dispex(&rect->dispex, (IUnknown*)&rect->IHTMLRect_iface, &HTMLRect_dispex);

    nsIDOMClientRect_AddRef(nsrect);
    rect->nsrect = nsrect;

    *ret = &rect->IHTMLRect_iface;
    return S_OK;
}