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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IDirectPlaySP_iface; int /*<<< orphan*/ * dplay; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_1__ IDirectPlaySPImpl ;
typedef  int /*<<< orphan*/  IDirectPlayImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectPlaySP_QueryInterface (TYPE_2__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IDirectPlaySP_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  directPlaySPVT ; 

HRESULT dplaysp_create( REFIID riid, void **ppv, IDirectPlayImpl *dp )
{
  IDirectPlaySPImpl *obj;
  HRESULT hr;

  TRACE( "(%s, %p)\n", debugstr_guid( riid ), ppv );

  *ppv = NULL;
  obj = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof( *obj ) );
  if ( !obj )
    return DPERR_OUTOFMEMORY;

  obj->IDirectPlaySP_iface.lpVtbl = &directPlaySPVT;
  obj->ref = 1;
  obj->dplay = dp;

  hr = IDirectPlaySP_QueryInterface( &obj->IDirectPlaySP_iface, riid, ppv );
  IDirectPlaySP_Release( &obj->IDirectPlaySP_iface );

  return hr;
}