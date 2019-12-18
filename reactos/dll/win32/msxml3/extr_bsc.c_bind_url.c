#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_4__ IBindStatusCallback_iface; int /*<<< orphan*/  hres; int /*<<< orphan*/ * memstream; int /*<<< orphan*/ * binding; int /*<<< orphan*/  (* onDataAvailable ) (void*,char*,DWORD) ;void* obj; } ;
typedef  TYPE_1__ bsc_t ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterBindStatusCallback (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsc_vtbl ; 
 TYPE_1__* heap_alloc (int) ; 

HRESULT bind_url(IMoniker *mon, HRESULT (*onDataAvailable)(void*,char*,DWORD),
        void *obj, bsc_t **ret)
{
    bsc_t *bsc;
    IBindCtx *pbc;
    HRESULT hr;

    TRACE("%p\n", mon);

    hr = CreateBindCtx(0, &pbc);
    if(FAILED(hr))
        return hr;

    bsc = heap_alloc(sizeof(bsc_t));

    bsc->IBindStatusCallback_iface.lpVtbl = &bsc_vtbl;
    bsc->ref = 1;
    bsc->obj = obj;
    bsc->onDataAvailable = onDataAvailable;
    bsc->binding = NULL;
    bsc->memstream = NULL;
    bsc->hres = S_OK;

    hr = RegisterBindStatusCallback(pbc, &bsc->IBindStatusCallback_iface, NULL, 0);
    if(SUCCEEDED(hr))
    {
        IStream *stream;
        hr = IMoniker_BindToStorage(mon, pbc, NULL, &IID_IStream, (LPVOID*)&stream);
        if(stream)
            IStream_Release(stream);
        IBindCtx_Release(pbc);
    }

    if(FAILED(hr))
    {
        IBindStatusCallback_Release(&bsc->IBindStatusCallback_iface);
        bsc = NULL;
    }

    *ret = bsc;
    return hr;
}