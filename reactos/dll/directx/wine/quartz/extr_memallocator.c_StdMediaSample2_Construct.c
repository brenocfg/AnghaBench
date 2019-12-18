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
struct TYPE_8__ {int cbData; int /*<<< orphan*/ * pbBuffer; scalar_t__ lActual; scalar_t__ cbBuffer; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {scalar_t__ tMediaEnd; int /*<<< orphan*/  tMediaStart; TYPE_3__ props; int /*<<< orphan*/ * pParent; scalar_t__ ref; TYPE_1__ IMediaSample2_iface; } ;
typedef  TYPE_2__ StdMediaSample2 ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IMemAllocator ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  AM_SAMPLE2_PROPERTIES ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  INVALID_MEDIA_TIME ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StdMediaSample2_VTable ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static HRESULT StdMediaSample2_Construct(BYTE * pbBuffer, LONG cbBuffer, IMemAllocator * pParent, StdMediaSample2 ** ppSample)
{
    assert(pbBuffer && pParent && (cbBuffer > 0));

    if (!(*ppSample = CoTaskMemAlloc(sizeof(StdMediaSample2))))
        return E_OUTOFMEMORY;

    (*ppSample)->IMediaSample2_iface.lpVtbl = &StdMediaSample2_VTable;
    (*ppSample)->ref = 0;
    ZeroMemory(&(*ppSample)->props, sizeof((*ppSample)->props));

    /* NOTE: no need to AddRef as the parent is guaranteed to be around
     * at least as long as us and we don't want to create circular
     * dependencies on the ref count */
    (*ppSample)->pParent = pParent;
    (*ppSample)->props.cbData = sizeof(AM_SAMPLE2_PROPERTIES);
    (*ppSample)->props.cbBuffer = (*ppSample)->props.lActual = cbBuffer;
    (*ppSample)->props.pbBuffer = pbBuffer;
    (*ppSample)->tMediaStart = INVALID_MEDIA_TIME;
    (*ppSample)->tMediaEnd = 0;

    return S_OK;
}