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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct midi_port {int ref; TYPE_2__ IDirectMusicPort_iface; int /*<<< orphan*/  clock; TYPE_1__ IDirectMusicThru_iface; } ;
typedef  TYPE_2__ IDirectMusicPort ;
typedef  int /*<<< orphan*/  IDirectMusic8Impl ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DMUS_PORTPARAMS ;
typedef  int /*<<< orphan*/  DMUS_PORTCAPS ;

/* Variables and functions */
 scalar_t__ DMUSIC_CreateReferenceClockImpl (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct midi_port*) ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 scalar_t__ S_OK ; 
 struct midi_port* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  midi_port_vtbl ; 
 int /*<<< orphan*/  midi_thru_vtbl ; 

__attribute__((used)) static HRESULT midi_port_create(IDirectMusic8Impl *parent, DMUS_PORTPARAMS *params,
        DMUS_PORTCAPS *caps, IDirectMusicPort **port)
{
    struct midi_port *obj;
    HRESULT hr;

    if (!(obj = heap_alloc_zero(sizeof(*obj))))
        return E_OUTOFMEMORY;

    obj->IDirectMusicPort_iface.lpVtbl = &midi_port_vtbl;
    obj->IDirectMusicThru_iface.lpVtbl = &midi_thru_vtbl;
    obj->ref = 1;

    hr = DMUSIC_CreateReferenceClockImpl(&IID_IReferenceClock, (void **)&obj->clock, NULL);
    if (hr != S_OK) {
        HeapFree(GetProcessHeap(), 0, obj);
        return hr;
    }

    *port = &obj->IDirectMusicPort_iface;

    return S_OK;
}