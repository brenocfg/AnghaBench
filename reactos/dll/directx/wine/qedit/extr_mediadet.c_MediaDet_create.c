#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int ref; int num_streams; TYPE_3__ IUnknown_inner; TYPE_3__* outer_unk; scalar_t__ cur_stream; int /*<<< orphan*/ * cur_pin; int /*<<< orphan*/ * splitter; int /*<<< orphan*/ * source; int /*<<< orphan*/ * graph; TYPE_1__ IMediaDet_iface; } ;
typedef  TYPE_2__ MediaDetImpl ;
typedef  TYPE_3__* LPVOID ;
typedef  TYPE_3__ IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IMediaDet_VTable ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mediadet_vtbl ; 

HRESULT MediaDet_create(IUnknown * pUnkOuter, LPVOID * ppv) {
    MediaDetImpl* obj = NULL;

    TRACE("(%p,%p)\n", pUnkOuter, ppv);

    obj = CoTaskMemAlloc(sizeof(MediaDetImpl));
    if (NULL == obj) {
        *ppv = NULL;
        return E_OUTOFMEMORY;
    }
    ZeroMemory(obj, sizeof(MediaDetImpl));

    obj->ref = 1;
    obj->IUnknown_inner.lpVtbl = &mediadet_vtbl;
    obj->IMediaDet_iface.lpVtbl = &IMediaDet_VTable;
    obj->graph = NULL;
    obj->source = NULL;
    obj->splitter = NULL;
    obj->cur_pin = NULL;
    obj->num_streams = -1;
    obj->cur_stream = 0;

    if (pUnkOuter)
        obj->outer_unk = pUnkOuter;
    else
        obj->outer_unk = &obj->IUnknown_inner;

    *ppv = &obj->IUnknown_inner;
    return S_OK;
}