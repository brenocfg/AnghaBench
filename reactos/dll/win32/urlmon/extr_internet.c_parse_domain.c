#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IInternetProtocolInfo_ParseUrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_DOMAIN ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  URL_PART_HOSTNAME ; 
 scalar_t__ UrlGetPartW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_protocol_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT parse_domain(LPCWSTR url, DWORD flags, LPWSTR result,
        DWORD size, DWORD *rsize)
{
    IInternetProtocolInfo *protocol_info;
    HRESULT hres;

    TRACE("(%s %08x %p %d %p)\n", debugstr_w(url), flags, result, size, rsize);

    protocol_info = get_protocol_info(url);

    if(protocol_info) {
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, url, PARSE_DOMAIN,
                flags, result, size, rsize, 0);
        IInternetProtocolInfo_Release(protocol_info);
        if(SUCCEEDED(hres))
            return hres;
    }

    hres = UrlGetPartW(url, result, &size, URL_PART_HOSTNAME, flags);
    if(rsize)
        *rsize = size;

    if(hres == E_POINTER)
        return S_FALSE;

    if(FAILED(hres))
        return E_FAIL;
    return S_OK;
}