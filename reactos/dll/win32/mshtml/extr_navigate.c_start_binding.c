#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * window; int /*<<< orphan*/  mon; int /*<<< orphan*/  IBindStatusCallback_iface; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IMoniker_BindToStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterBindStatusCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

HRESULT start_binding(HTMLInnerWindow *inner_window, BSCallback *bscallback, IBindCtx *bctx)
{
    IStream *str = NULL;
    HRESULT hres;

    TRACE("(%p %p %p)\n", inner_window, bscallback, bctx);

    bscallback->window = inner_window;

    /* NOTE: IE7 calls IsSystemMoniker here*/

    if(bctx) {
        hres = RegisterBindStatusCallback(bctx, &bscallback->IBindStatusCallback_iface, NULL, 0);
        if(SUCCEEDED(hres))
            IBindCtx_AddRef(bctx);
    }else {
        hres = CreateAsyncBindCtx(0, &bscallback->IBindStatusCallback_iface, NULL, &bctx);
    }

    if(FAILED(hres)) {
        bscallback->window = NULL;
        return hres;
    }

    hres = IMoniker_BindToStorage(bscallback->mon, bctx, NULL, &IID_IStream, (void**)&str);
    IBindCtx_Release(bctx);
    if(FAILED(hres)) {
        WARN("BindToStorage failed: %08x\n", hres);
        bscallback->window = NULL;
        return hres;
    }

    if(str)
        IStream_Release(str);

    return S_OK;
}