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
struct TYPE_6__ {int bindf; int /*<<< orphan*/  request; int /*<<< orphan*/  protocol_sink; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  IWindowForBindingUI ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  IID ;
typedef  int /*<<< orphan*/  IHttpSecurity ;
typedef  TYPE_2__ HttpProtocol ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BINDF_NO_UI ; 
 int /*<<< orphan*/  ERR (char*) ; 
#define  ERROR_HTTP_REDIRECT_NEEDS_CONFIRMATION 139 
#define  ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED 138 
 int ERROR_INTERNET_FORCE_RETRY ; 
#define  ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR 137 
#define  ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR 136 
 int ERROR_INTERNET_INCORRECT_PASSWORD ; 
#define  ERROR_INTERNET_INVALID_CA 135 
#define  ERROR_INTERNET_SEC_CERT_CN_INVALID 134 
#define  ERROR_INTERNET_SEC_CERT_DATE_INVALID 133 
#define  ERROR_INTERNET_SEC_CERT_ERRORS 132 
#define  ERROR_INTERNET_SEC_CERT_NO_REV 131 
#define  ERROR_INTERNET_SEC_CERT_REVOKED 130 
#define  ERROR_INTERNET_SEC_CERT_REV_FAILED 129 
#define  ERROR_INTERNET_SEC_INVALID_CERT 128 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_ABORT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS ; 
 int FLAGS_ERROR_UI_FLAGS_GENERATE_DATA ; 
 int FLAGS_ERROR_UI_FLAGS_NO_UI ; 
 int /*<<< orphan*/  IHttpSecurity_OnSecurityProblem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IHttpSecurity_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAuthenticate ; 
 int /*<<< orphan*/  IID_IHttpSecurity ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IID_IWindowForBindingUI ; 
 int /*<<< orphan*/  IInternetProtocolSink_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IServiceProvider_QueryService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWindowForBindingUI_GetWindow (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWindowForBindingUI_Release (int /*<<< orphan*/ *) ; 
 int InternetErrorDlg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_E_RETRY ; 
 int /*<<< orphan*/  SECURITY_FLAG_IGNORE_CERT_CN_INVALID ; 
 int /*<<< orphan*/  SECURITY_FLAG_IGNORE_CERT_DATE_INVALID ; 
 int /*<<< orphan*/  SECURITY_FLAG_IGNORE_REVOCATION ; 
 int /*<<< orphan*/  SECURITY_FLAG_IGNORE_UNKNOWN_CA ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  internet_error_to_hres (int) ; 
 scalar_t__ set_security_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT handle_http_error(HttpProtocol *This, DWORD error)
{
    IServiceProvider *serv_prov;
    IWindowForBindingUI *wfb_ui;
    IHttpSecurity *http_security;
    BOOL security_problem;
    DWORD dlg_flags;
    HWND hwnd;
    DWORD res;
    HRESULT hres;

    TRACE("(%p %u)\n", This, error);

    switch(error) {
    case ERROR_INTERNET_SEC_CERT_DATE_INVALID:
    case ERROR_INTERNET_SEC_CERT_CN_INVALID:
    case ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR:
    case ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR:
    case ERROR_INTERNET_INVALID_CA:
    case ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED:
    case ERROR_INTERNET_SEC_INVALID_CERT:
    case ERROR_INTERNET_SEC_CERT_ERRORS:
    case ERROR_INTERNET_SEC_CERT_REV_FAILED:
    case ERROR_INTERNET_SEC_CERT_NO_REV:
    case ERROR_INTERNET_SEC_CERT_REVOKED:
    case ERROR_HTTP_REDIRECT_NEEDS_CONFIRMATION:
        security_problem = TRUE;
        break;
    default:
        security_problem = FALSE;
    }

    hres = IInternetProtocolSink_QueryInterface(This->base.protocol_sink, &IID_IServiceProvider,
                                                (void**)&serv_prov);
    if(FAILED(hres)) {
        ERR("Failed to get IServiceProvider.\n");
        return E_ABORT;
    }

    if(security_problem) {
        hres = IServiceProvider_QueryService(serv_prov, &IID_IHttpSecurity, &IID_IHttpSecurity,
                                             (void**)&http_security);
        if(SUCCEEDED(hres)) {
            hres = IHttpSecurity_OnSecurityProblem(http_security, error);
            IHttpSecurity_Release(http_security);

            TRACE("OnSecurityProblem returned %08x\n", hres);

            if(hres != S_FALSE)
            {
                BOOL res = FALSE;

                IServiceProvider_Release(serv_prov);

                if(hres == S_OK) {
                    if(error == ERROR_INTERNET_SEC_CERT_DATE_INVALID)
                        res = set_security_flag(This, SECURITY_FLAG_IGNORE_CERT_DATE_INVALID);
                    else if(error == ERROR_INTERNET_SEC_CERT_CN_INVALID)
                        res = set_security_flag(This, SECURITY_FLAG_IGNORE_CERT_CN_INVALID);
                    else if(error == ERROR_INTERNET_INVALID_CA)
                        res = set_security_flag(This, SECURITY_FLAG_IGNORE_UNKNOWN_CA);

                    if(res)
                        return RPC_E_RETRY;

                    FIXME("Don't know how to ignore error %d\n", error);
                    return E_ABORT;
                }

                if(hres == E_ABORT)
                    return E_ABORT;
                if(hres == RPC_E_RETRY)
                    return RPC_E_RETRY;

                return internet_error_to_hres(error);
            }
        }
    }

    switch(error) {
    case ERROR_INTERNET_SEC_CERT_REV_FAILED:
        if(hres != S_FALSE) {
            /* Silently ignore the error. We will get more detailed error from wininet anyway. */
            set_security_flag(This, SECURITY_FLAG_IGNORE_REVOCATION);
            hres = RPC_E_RETRY;
            break;
        }
        /* fallthrough */
    default:
        hres = IServiceProvider_QueryService(serv_prov, &IID_IWindowForBindingUI, &IID_IWindowForBindingUI, (void**)&wfb_ui);
        if(SUCCEEDED(hres)) {
            const IID *iid_reason;

            if(security_problem)
                iid_reason = &IID_IHttpSecurity;
            else if(error == ERROR_INTERNET_INCORRECT_PASSWORD)
                iid_reason = &IID_IAuthenticate;
            else
                iid_reason = &IID_IWindowForBindingUI;

            hres = IWindowForBindingUI_GetWindow(wfb_ui, iid_reason, &hwnd);
            IWindowForBindingUI_Release(wfb_ui);
        }

        if(FAILED(hres)) hwnd = NULL;

        dlg_flags = FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS | FLAGS_ERROR_UI_FLAGS_GENERATE_DATA;
        if(This->base.bindf & BINDF_NO_UI)
            dlg_flags |= FLAGS_ERROR_UI_FLAGS_NO_UI;

        res = InternetErrorDlg(hwnd, This->base.request, error, dlg_flags, NULL);
        hres = res == ERROR_INTERNET_FORCE_RETRY || res == ERROR_SUCCESS ? RPC_E_RETRY : internet_error_to_hres(error);
    }

    IServiceProvider_Release(serv_prov);
    return hres;
}