#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  IInternetProtocolEx_iface; } ;
struct TYPE_9__ {scalar_t__ download_state; int bindf; int state; int /*<<< orphan*/  notif_hwnd; int /*<<< orphan*/  IBinding_iface; int /*<<< orphan*/  IInternetBindInfo_iface; int /*<<< orphan*/  IInternetProtocolSink_iface; TYPE_5__* protocol; scalar_t__ redirect_url; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ Binding ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BINDF_ASYNCHRONOUS ; 
 int BINDING_STOPPED ; 
 int /*<<< orphan*/  BINDSTATUS_REDIRECTING ; 
 int BSCF_FIRSTDATANOTIFICATION ; 
 int BSCF_LASTDATANOTIFICATION ; 
 scalar_t__ Binding_Create (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  DispatchMessageW (int /*<<< orphan*/ *) ; 
 scalar_t__ END_DOWNLOAD ; 
 scalar_t__ E_ABORT ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_PENDING ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IBindStatusCallback_OnProgress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IBindStatusCallback_OnStartBinding (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBinding_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetProtocolEx_StartEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ INET_E_DOWNLOAD_FAILURE ; 
 int /*<<< orphan*/  MsgWaitForMultipleObjects (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int PI_APARTMENTTHREADED ; 
 int PI_MIMEVERIFICATION ; 
 int PM_NOYIELD ; 
 int PM_REMOVE ; 
 scalar_t__ PeekMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  QS_POSTMESSAGE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ WM_USER ; 
 int /*<<< orphan*/  report_data (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_binding_sink (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_binding (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT start_binding(IMoniker *mon, Binding *binding_ctx, IUri *uri, IBindCtx *pbc,
                             BOOL to_obj, REFIID riid, Binding **ret)
{
    Binding *binding = NULL;
    HRESULT hres;
    MSG msg;

    hres = Binding_Create(mon, binding_ctx, uri, pbc, to_obj, riid, &binding);
    if(FAILED(hres))
        return hres;

    hres = IBindStatusCallback_OnStartBinding(binding->callback, 0, &binding->IBinding_iface);
    if(FAILED(hres)) {
        WARN("OnStartBinding failed: %08x\n", hres);
        if(hres != E_ABORT && hres != E_NOTIMPL)
            hres = INET_E_DOWNLOAD_FAILURE;

        stop_binding(binding, hres, NULL);
        IBinding_Release(&binding->IBinding_iface);
        return hres;
    }

    if(binding_ctx) {
        set_binding_sink(binding->protocol, &binding->IInternetProtocolSink_iface,
                &binding->IInternetBindInfo_iface);
        if(binding_ctx->redirect_url)
            IBindStatusCallback_OnProgress(binding->callback, 0, 0, BINDSTATUS_REDIRECTING, binding_ctx->redirect_url);
        report_data(binding, BSCF_FIRSTDATANOTIFICATION | (binding_ctx->download_state == END_DOWNLOAD ? BSCF_LASTDATANOTIFICATION : 0),
                0, 0);
    }else {
        hres = IInternetProtocolEx_StartEx(&binding->protocol->IInternetProtocolEx_iface, uri,
                &binding->IInternetProtocolSink_iface, &binding->IInternetBindInfo_iface,
                PI_APARTMENTTHREADED|PI_MIMEVERIFICATION, 0);

        TRACE("start ret %08x\n", hres);

        if(FAILED(hres) && hres != E_PENDING) {
            stop_binding(binding, hres, NULL);
            IBinding_Release(&binding->IBinding_iface);

            return hres;
        }
    }

    while(!(binding->bindf & BINDF_ASYNCHRONOUS) &&
          !(binding->state & BINDING_STOPPED)) {
        MsgWaitForMultipleObjects(0, NULL, FALSE, 5000, QS_POSTMESSAGE);
        while (PeekMessageW(&msg, binding->notif_hwnd, WM_USER, WM_USER+117, PM_REMOVE|PM_NOYIELD)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    *ret = binding;
    return S_OK;
}