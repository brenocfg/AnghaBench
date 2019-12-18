#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url_info ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int cbSize; int nScheme; int cchSuffix; char* pszSuffix; scalar_t__ cchProtocol; } ;
typedef  TYPE_1__ PARSEDURLW ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_POINTER ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_ParseUrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_ROOTDOCUMENT ; 
 int /*<<< orphan*/  ParseURLW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  URL_PART_HOSTNAME ; 
#define  URL_SCHEME_FTP 130 
#define  URL_SCHEME_HTTP 129 
#define  URL_SCHEME_HTTPS 128 
 int /*<<< orphan*/  UrlGetPartW (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_protocol_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT parse_rootdocument(LPCWSTR url, DWORD flags, LPWSTR result,
        DWORD size, DWORD *rsize)
{
    IInternetProtocolInfo *protocol_info;
    PARSEDURLW url_info;
    HRESULT hres;

    TRACE("(%s %08x %p %d %p)\n", debugstr_w(url), flags, result, size, rsize);

    protocol_info = get_protocol_info(url);

    if(protocol_info) {
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, url, PARSE_ROOTDOCUMENT,
                flags, result, size, rsize, 0);
        IInternetProtocolInfo_Release(protocol_info);
        if(SUCCEEDED(hres))
            return hres;
    }

    url_info.cbSize = sizeof(url_info);
    if(FAILED(ParseURLW(url, &url_info)))
        return E_FAIL;

    switch(url_info.nScheme) {
        case URL_SCHEME_FTP:
        case URL_SCHEME_HTTP:
        case URL_SCHEME_HTTPS:
            if(url_info.cchSuffix<3 || *(url_info.pszSuffix)!='/'
                    || *(url_info.pszSuffix+1)!='/')
                return E_FAIL;

            if(size < url_info.cchProtocol+3) {
                size = 0;
                hres = UrlGetPartW(url, result, &size, URL_PART_HOSTNAME, flags);

                if(rsize)
                    *rsize = size+url_info.cchProtocol+3;

                if(hres == E_POINTER)
                    return S_FALSE;

                return hres;
            }

            size -= url_info.cchProtocol+3;
            hres = UrlGetPartW(url, result+url_info.cchProtocol+3,
                    &size, URL_PART_HOSTNAME, flags);

            if(hres == E_POINTER)
                return S_FALSE;

            if(FAILED(hres))
                return E_FAIL;

            if(rsize)
                *rsize = size+url_info.cchProtocol+3;

            memcpy(result, url, (url_info.cchProtocol+3)*sizeof(WCHAR));
            return hres;
        default:
            return E_FAIL;
    }
}