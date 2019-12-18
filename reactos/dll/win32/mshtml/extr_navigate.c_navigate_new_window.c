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
struct TYPE_7__ {int /*<<< orphan*/  post_data_len; int /*<<< orphan*/ * post_data; int /*<<< orphan*/ * headers; } ;
typedef  TYPE_2__ request_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_8__ {TYPE_1__ bsc; } ;
typedef  TYPE_3__ nsChannelBSC ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IWebBrowser2 ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITargetFramePriv2 ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_InternetExplorer ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int HLNF_DISABLEWINDOWRESTRICTIONS ; 
 int HLNF_OPENINNEWWINDOW ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLWindow2 ; 
 int /*<<< orphan*/  IID_ITargetFramePriv2 ; 
 int /*<<< orphan*/  IID_IWebBrowser2 ; 
 int /*<<< orphan*/  ITargetFramePriv2_AggregatedNavigation2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITargetFramePriv2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWebBrowser2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWebBrowser2_Quit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWebBrowser2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWebBrowser2_put_Visible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SID_SHTMLWindow ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_channelbsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  do_query_service (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  emptyW ; 

HRESULT navigate_new_window(HTMLOuterWindow *window, IUri *uri, const WCHAR *name, request_data_t *request_data, IHTMLWindow2 **ret)
{
    IWebBrowser2 *web_browser;
    IHTMLWindow2 *new_window;
    IBindCtx *bind_ctx;
    nsChannelBSC *bsc;
    HRESULT hres;

    if(request_data)
        hres = create_channelbsc(NULL, request_data->headers,
                request_data->post_data, request_data->post_data_len, FALSE,
                &bsc);
    else
        hres = create_channelbsc(NULL, NULL, NULL, 0, FALSE, &bsc);
    if(FAILED(hres))
        return hres;

    hres = CreateAsyncBindCtx(0, &bsc->bsc.IBindStatusCallback_iface, NULL, &bind_ctx);
    if(FAILED(hres)) {
        IBindStatusCallback_Release(&bsc->bsc.IBindStatusCallback_iface);
        return hres;
    }

    hres = CoCreateInstance(&CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER,
            &IID_IWebBrowser2, (void**)&web_browser);
    if(SUCCEEDED(hres)) {
        ITargetFramePriv2 *target_frame_priv;

        hres = IWebBrowser2_QueryInterface(web_browser, &IID_ITargetFramePriv2, (void**)&target_frame_priv);
        if(SUCCEEDED(hres)) {
            hres = ITargetFramePriv2_AggregatedNavigation2(target_frame_priv,
                    HLNF_DISABLEWINDOWRESTRICTIONS|HLNF_OPENINNEWWINDOW, bind_ctx, &bsc->bsc.IBindStatusCallback_iface,
                    name, uri, emptyW);
            ITargetFramePriv2_Release(target_frame_priv);

            if(SUCCEEDED(hres))
                hres = do_query_service((IUnknown*)web_browser, &SID_SHTMLWindow, &IID_IHTMLWindow2, (void**)&new_window);
        }
        if(FAILED(hres)) {
            IWebBrowser2_Quit(web_browser);
            IWebBrowser2_Release(web_browser);
        }
    }else {
        WARN("Could not create InternetExplorer instance: %08x\n", hres);
    }

    IBindStatusCallback_Release(&bsc->bsc.IBindStatusCallback_iface);
    IBindCtx_Release(bind_ctx);
    if(FAILED(hres))
        return hres;

    IWebBrowser2_put_Visible(web_browser, VARIANT_TRUE);
    IWebBrowser2_Release(web_browser);

    if(ret)
        *ret = new_window;
    else
        IHTMLWindow2_Release(new_window);
    return S_OK;
}