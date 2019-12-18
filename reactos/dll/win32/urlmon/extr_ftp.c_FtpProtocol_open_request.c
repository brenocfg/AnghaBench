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
struct TYPE_4__ {int /*<<< orphan*/  request; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Protocol ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IInternetBindInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  TYPE_2__ FtpProtocol ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INET_E_RESOURCE_NOT_FOUND ; 
 int INTERNET_FLAG_EXISTING_CONNECT ; 
 int INTERNET_FLAG_PASSIVE ; 
 int /*<<< orphan*/  IUri_GetAbsoluteUri (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetOpenUrlW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 TYPE_2__* impl_from_Protocol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT FtpProtocol_open_request(Protocol *prot, IUri *uri, DWORD request_flags,
        HINTERNET internet_session, IInternetBindInfo *bind_info)
{
    FtpProtocol *This = impl_from_Protocol(prot);
    BSTR url;
    HRESULT hres;

    hres = IUri_GetAbsoluteUri(uri, &url);
    if(FAILED(hres))
        return hres;

    This->base.request = InternetOpenUrlW(internet_session, url, NULL, 0,
            request_flags|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_PASSIVE,
            (DWORD_PTR)&This->base);
    SysFreeString(url);
    if (!This->base.request && GetLastError() != ERROR_IO_PENDING) {
        WARN("InternetOpenUrl failed: %d\n", GetLastError());
        return INET_E_RESOURCE_NOT_FOUND;
    }

    return S_OK;
}