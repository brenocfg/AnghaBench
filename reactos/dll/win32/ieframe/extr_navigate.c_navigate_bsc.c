#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  void* VARIANT_BOOL ;
struct TYPE_18__ {int /*<<< orphan*/  IBindStatusCallback_iface; int /*<<< orphan*/  url; int /*<<< orphan*/  headers; int /*<<< orphan*/  post_data_len; scalar_t__ post_data; } ;
struct TYPE_17__ {scalar_t__ frame; scalar_t__ document; void* busy; } ;
struct TYPE_16__ {int /*<<< orphan*/  pvData; } ;
typedef  TYPE_1__ SAFEARRAY ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DocHost ;
typedef  TYPE_3__ BindStatusCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CSC_NAVIGATEBACK ; 
 int /*<<< orphan*/  CSC_NAVIGATEFORWARD ; 
 int /*<<< orphan*/  CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceFrame_EnableModeless (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READYSTATE_LOADING ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* SafeArrayCreateVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SafeArrayDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* VARIANT_FALSE ; 
 int /*<<< orphan*/  VT_UI1 ; 
 int /*<<< orphan*/  bind_to_object (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deactivate_document (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_download_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_before_navigate2 (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  on_commandstate_change (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_doc_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT navigate_bsc(DocHost *This, BindStatusCallback *bsc, IMoniker *mon)
{
    VARIANT_BOOL cancel = VARIANT_FALSE;
    SAFEARRAY *post_data = NULL;
    IBindCtx *bindctx;
    HRESULT hres;

    set_doc_state(This, READYSTATE_LOADING);

    if(bsc->post_data) {
        post_data = SafeArrayCreateVector(VT_UI1, 0, bsc->post_data_len);
        memcpy(post_data->pvData, post_data, bsc->post_data_len);
    }

    on_before_navigate2(This, bsc->url, post_data, bsc->headers, &cancel);
    if(post_data)
        SafeArrayDestroy(post_data);
    if(cancel) {
        FIXME("Navigation canceled\n");
        return S_OK;
    }

    notify_download_state(This, TRUE);
    This->busy = VARIANT_FALSE;

    on_commandstate_change(This, CSC_NAVIGATEBACK, FALSE);
    on_commandstate_change(This, CSC_NAVIGATEFORWARD, FALSE);

    if(This->document)
        deactivate_document(This);

    CreateAsyncBindCtx(0, &bsc->IBindStatusCallback_iface, 0, &bindctx);

    if(This->frame)
        IOleInPlaceFrame_EnableModeless(This->frame, FALSE);

    hres = bind_to_object(This, mon, bsc->url, bindctx, &bsc->IBindStatusCallback_iface);

    if(This->frame)
        IOleInPlaceFrame_EnableModeless(This->frame, TRUE);

    IBindCtx_Release(bindctx);

    return hres;
}