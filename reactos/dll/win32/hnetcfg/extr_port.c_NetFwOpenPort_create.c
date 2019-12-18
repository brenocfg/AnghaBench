#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refs; TYPE_2__ INetFwOpenPort_iface; scalar_t__ port; int /*<<< orphan*/  protocol; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ fw_port ;
typedef  TYPE_2__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NET_FW_IP_PROTOCOL_TCP ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  fw_port_vtbl ; 

HRESULT NetFwOpenPort_create( IUnknown *pUnkOuter, LPVOID *ppObj )
{
    fw_port *fp;

    TRACE("(%p,%p)\n", pUnkOuter, ppObj);

    fp = HeapAlloc( GetProcessHeap(), 0, sizeof(*fp) );
    if (!fp) return E_OUTOFMEMORY;

    fp->INetFwOpenPort_iface.lpVtbl = &fw_port_vtbl;
    fp->refs = 1;
    fp->name = NULL;
    fp->protocol = NET_FW_IP_PROTOCOL_TCP;
    fp->port = 0;

    *ppObj = &fp->INetFwOpenPort_iface;

    TRACE("returning iface %p\n", *ppObj);
    return S_OK;
}