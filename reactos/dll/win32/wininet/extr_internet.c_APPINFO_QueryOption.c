#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  object_header_t ;
struct TYPE_4__ {int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  proxyBypass; int /*<<< orphan*/  proxy; int /*<<< orphan*/  accessType; int /*<<< orphan*/  agent; } ;
typedef  TYPE_1__ appinfo_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/ * lpszProxyBypass; int /*<<< orphan*/ * lpszProxy; int /*<<< orphan*/  dwAccessType; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpszProxyBypass; int /*<<< orphan*/ * lpszProxy; int /*<<< orphan*/  dwAccessType; } ;
typedef  void* LPWSTR ;
typedef  void* LPSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_2__ INTERNET_PROXY_INFOW ;
typedef  TYPE_3__ INTERNET_PROXY_INFOA ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int INET_QueryOption (int /*<<< orphan*/ *,int,void*,int*,int /*<<< orphan*/ ) ; 
 int INTERNET_HANDLE_TYPE_INTERNET ; 
#define  INTERNET_OPTION_CONNECT_TIMEOUT 131 
#define  INTERNET_OPTION_HANDLE_TYPE 130 
#define  INTERNET_OPTION_PROXY 129 
#define  INTERNET_OPTION_USER_AGENT 128 
 int /*<<< orphan*/  TRACE (char*) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (void*,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD APPINFO_QueryOption(object_header_t *hdr, DWORD option, void *buffer, DWORD *size, BOOL unicode)
{
    appinfo_t *ai = (appinfo_t*)hdr;

    switch(option) {
    case INTERNET_OPTION_HANDLE_TYPE:
        TRACE("INTERNET_OPTION_HANDLE_TYPE\n");

        if (*size < sizeof(ULONG))
            return ERROR_INSUFFICIENT_BUFFER;

        *size = sizeof(DWORD);
        *(DWORD*)buffer = INTERNET_HANDLE_TYPE_INTERNET;
        return ERROR_SUCCESS;

    case INTERNET_OPTION_USER_AGENT: {
        DWORD bufsize;

        TRACE("INTERNET_OPTION_USER_AGENT\n");

        bufsize = *size;

        if (unicode) {
            DWORD len = ai->agent ? strlenW(ai->agent) : 0;

            *size = (len + 1) * sizeof(WCHAR);
            if(!buffer || bufsize < *size)
                return ERROR_INSUFFICIENT_BUFFER;

            if (ai->agent)
                strcpyW(buffer, ai->agent);
            else
                *(WCHAR *)buffer = 0;
            /* If the buffer is copied, the returned length doesn't include
             * the NULL terminator.
             */
            *size = len;
        }else {
            if (ai->agent)
                *size = WideCharToMultiByte(CP_ACP, 0, ai->agent, -1, NULL, 0, NULL, NULL);
            else
                *size = 1;
            if(!buffer || bufsize < *size)
                return ERROR_INSUFFICIENT_BUFFER;

            if (ai->agent)
                WideCharToMultiByte(CP_ACP, 0, ai->agent, -1, buffer, *size, NULL, NULL);
            else
                *(char *)buffer = 0;
            /* If the buffer is copied, the returned length doesn't include
             * the NULL terminator.
             */
            *size -= 1;
        }

        return ERROR_SUCCESS;
    }

    case INTERNET_OPTION_PROXY:
        if(!size) return ERROR_INVALID_PARAMETER;
        if (unicode) {
            INTERNET_PROXY_INFOW *pi = (INTERNET_PROXY_INFOW *)buffer;
            DWORD proxyBytesRequired = 0, proxyBypassBytesRequired = 0;
            LPWSTR proxy, proxy_bypass;

            if (ai->proxy)
                proxyBytesRequired = (lstrlenW(ai->proxy) + 1) * sizeof(WCHAR);
            if (ai->proxyBypass)
                proxyBypassBytesRequired = (lstrlenW(ai->proxyBypass) + 1) * sizeof(WCHAR);
            if (!pi || *size < sizeof(INTERNET_PROXY_INFOW) + proxyBytesRequired + proxyBypassBytesRequired)
            {
                *size = sizeof(INTERNET_PROXY_INFOW) + proxyBytesRequired + proxyBypassBytesRequired;
                return ERROR_INSUFFICIENT_BUFFER;
            }
            proxy = (LPWSTR)((LPBYTE)buffer + sizeof(INTERNET_PROXY_INFOW));
            proxy_bypass = (LPWSTR)((LPBYTE)buffer + sizeof(INTERNET_PROXY_INFOW) + proxyBytesRequired);

            pi->dwAccessType = ai->accessType;
            pi->lpszProxy = NULL;
            pi->lpszProxyBypass = NULL;
            if (ai->proxy) {
                lstrcpyW(proxy, ai->proxy);
                pi->lpszProxy = proxy;
            }

            if (ai->proxyBypass) {
                lstrcpyW(proxy_bypass, ai->proxyBypass);
                pi->lpszProxyBypass = proxy_bypass;
            }

            *size = sizeof(INTERNET_PROXY_INFOW) + proxyBytesRequired + proxyBypassBytesRequired;
            return ERROR_SUCCESS;
        }else {
            INTERNET_PROXY_INFOA *pi = (INTERNET_PROXY_INFOA *)buffer;
            DWORD proxyBytesRequired = 0, proxyBypassBytesRequired = 0;
            LPSTR proxy, proxy_bypass;

            if (ai->proxy)
                proxyBytesRequired = WideCharToMultiByte(CP_ACP, 0, ai->proxy, -1, NULL, 0, NULL, NULL);
            if (ai->proxyBypass)
                proxyBypassBytesRequired = WideCharToMultiByte(CP_ACP, 0, ai->proxyBypass, -1,
                        NULL, 0, NULL, NULL);
            if (!pi || *size < sizeof(INTERNET_PROXY_INFOA) + proxyBytesRequired + proxyBypassBytesRequired)
            {
                *size = sizeof(INTERNET_PROXY_INFOA) + proxyBytesRequired + proxyBypassBytesRequired;
                return ERROR_INSUFFICIENT_BUFFER;
            }
            proxy = (LPSTR)((LPBYTE)buffer + sizeof(INTERNET_PROXY_INFOA));
            proxy_bypass = (LPSTR)((LPBYTE)buffer + sizeof(INTERNET_PROXY_INFOA) + proxyBytesRequired);

            pi->dwAccessType = ai->accessType;
            pi->lpszProxy = NULL;
            pi->lpszProxyBypass = NULL;
            if (ai->proxy) {
                WideCharToMultiByte(CP_ACP, 0, ai->proxy, -1, proxy, proxyBytesRequired, NULL, NULL);
                pi->lpszProxy = proxy;
            }

            if (ai->proxyBypass) {
                WideCharToMultiByte(CP_ACP, 0, ai->proxyBypass, -1, proxy_bypass,
                        proxyBypassBytesRequired, NULL, NULL);
                pi->lpszProxyBypass = proxy_bypass;
            }

            *size = sizeof(INTERNET_PROXY_INFOA) + proxyBytesRequired + proxyBypassBytesRequired;
            return ERROR_SUCCESS;
        }

    case INTERNET_OPTION_CONNECT_TIMEOUT:
        TRACE("INTERNET_OPTION_CONNECT_TIMEOUT\n");

        if (*size < sizeof(ULONG))
            return ERROR_INSUFFICIENT_BUFFER;

        *(ULONG*)buffer = ai->connect_timeout;
        *size = sizeof(ULONG);

        return ERROR_SUCCESS;
    }

    return INET_QueryOption(hdr, option, buffer, size, unicode);
}