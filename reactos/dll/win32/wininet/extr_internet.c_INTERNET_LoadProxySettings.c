#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int proxyEnabled; char* proxy; char* proxyBypass; } ;
typedef  TYPE_1__ proxyinfo_t ;
typedef  char WCHAR ;
struct TYPE_8__ {int proxyEnabled; int /*<<< orphan*/  proxyBypass; int /*<<< orphan*/  proxy; } ;
typedef  char* LPWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UNIXCP ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeProxyInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*,scalar_t__) ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WININET_cs ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 scalar_t__ getenv (char*) ; 
 TYPE_4__* global_proxy ; 
 void* heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 void* heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  lstrlenW (char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_proxy_url (TYPE_1__*,char*) ; 
 char* strchrW (char*,char) ; 
 char* strstrW (char*,char const*) ; 
 int /*<<< orphan*/  szInternetSettings ; 
 int /*<<< orphan*/  szProxyEnable ; 
 int /*<<< orphan*/  szProxyOverride ; 
 int /*<<< orphan*/  szProxyServer ; 

__attribute__((used)) static LONG INTERNET_LoadProxySettings( proxyinfo_t *lpwpi )
{
    HKEY key;
    DWORD type, len;
    LPCSTR envproxy;
    LONG ret;

    memset( lpwpi, 0, sizeof(*lpwpi) );

    EnterCriticalSection( &WININET_cs );
    if (global_proxy)
    {
        lpwpi->proxyEnabled = global_proxy->proxyEnabled;
        lpwpi->proxy = heap_strdupW( global_proxy->proxy );
        lpwpi->proxyBypass = heap_strdupW( global_proxy->proxyBypass );
    }
    LeaveCriticalSection( &WININET_cs );

    if ((ret = RegOpenKeyW( HKEY_CURRENT_USER, szInternetSettings, &key )))
    {
        FreeProxyInfo( lpwpi );
        return ret;
    }

    len = sizeof(DWORD);
    if (RegQueryValueExW( key, szProxyEnable, NULL, &type, (BYTE *)&lpwpi->proxyEnabled, &len ) || type != REG_DWORD)
    {
        lpwpi->proxyEnabled = 0;
        if((ret = RegSetValueExW( key, szProxyEnable, 0, REG_DWORD, (BYTE *)&lpwpi->proxyEnabled, sizeof(DWORD) )))
        {
            FreeProxyInfo( lpwpi );
            RegCloseKey( key );
            return ret;
        }
    }

    if (!(envproxy = getenv( "http_proxy" )) || lpwpi->proxyEnabled)
    {
        /* figure out how much memory the proxy setting takes */
        if (!RegQueryValueExW( key, szProxyServer, NULL, &type, NULL, &len ) && len && (type == REG_SZ))
        {
            LPWSTR szProxy, p;
            static const WCHAR szHttp[] = {'h','t','t','p','=',0};

            if (!(szProxy = heap_alloc(len)))
            {
                RegCloseKey( key );
                FreeProxyInfo( lpwpi );
                return ERROR_OUTOFMEMORY;
            }
            RegQueryValueExW( key, szProxyServer, NULL, &type, (BYTE*)szProxy, &len );

            /* find the http proxy, and strip away everything else */
            p = strstrW( szProxy, szHttp );
            if (p)
            {
                p += lstrlenW( szHttp );
                lstrcpyW( szProxy, p );
            }
            p = strchrW( szProxy, ';' );
            if (p) *p = 0;

            FreeProxyInfo( lpwpi );
            lpwpi->proxy = szProxy;
            lpwpi->proxyBypass = NULL;

            TRACE("http proxy (from registry) = %s\n", debugstr_w(lpwpi->proxy));
        }
        else
        {
            TRACE("No proxy server settings in registry.\n");
            FreeProxyInfo( lpwpi );
            lpwpi->proxy = NULL;
            lpwpi->proxyBypass = NULL;
        }
    }
    else if (envproxy)
    {
        WCHAR *envproxyW;

        len = MultiByteToWideChar( CP_UNIXCP, 0, envproxy, -1, NULL, 0 );
        if (!(envproxyW = heap_alloc(len * sizeof(WCHAR))))
        {
            RegCloseKey( key );
            return ERROR_OUTOFMEMORY;
        }
        MultiByteToWideChar( CP_UNIXCP, 0, envproxy, -1, envproxyW, len );

        FreeProxyInfo( lpwpi );
        if (parse_proxy_url( lpwpi, envproxyW ))
        {
            TRACE("http proxy (from environment) = %s\n", debugstr_w(lpwpi->proxy));
            lpwpi->proxyEnabled = 1;
            lpwpi->proxyBypass = NULL;
        }
        else
        {
            WARN("failed to parse http_proxy value %s\n", debugstr_w(envproxyW));
            lpwpi->proxyEnabled = 0;
            lpwpi->proxy = NULL;
            lpwpi->proxyBypass = NULL;
        }
        heap_free( envproxyW );
    }

    if (lpwpi->proxyEnabled)
    {
        TRACE("Proxy is enabled.\n");

        if (!(envproxy = getenv( "no_proxy" )))
        {
            /* figure out how much memory the proxy setting takes */
            if (!RegQueryValueExW( key, szProxyOverride, NULL, &type, NULL, &len ) && len && (type == REG_SZ))
            {
                LPWSTR szProxy;

                if (!(szProxy = heap_alloc(len)))
                {
                    RegCloseKey( key );
                    return ERROR_OUTOFMEMORY;
                }
                RegQueryValueExW( key, szProxyOverride, NULL, &type, (BYTE*)szProxy, &len );

                heap_free( lpwpi->proxyBypass );
                lpwpi->proxyBypass = szProxy;

                TRACE("http proxy bypass (from registry) = %s\n", debugstr_w(lpwpi->proxyBypass));
            }
            else
            {
                heap_free( lpwpi->proxyBypass );
                lpwpi->proxyBypass = NULL;

                TRACE("No proxy bypass server settings in registry.\n");
            }
        }
        else
        {
            WCHAR *envproxyW;

            len = MultiByteToWideChar( CP_UNIXCP, 0, envproxy, -1, NULL, 0 );
            if (!(envproxyW = heap_alloc(len * sizeof(WCHAR))))
            {
                RegCloseKey( key );
                return ERROR_OUTOFMEMORY;
            }
            MultiByteToWideChar( CP_UNIXCP, 0, envproxy, -1, envproxyW, len );

            heap_free( lpwpi->proxyBypass );
            lpwpi->proxyBypass = envproxyW;

            TRACE("http proxy bypass (from environment) = %s\n", debugstr_w(lpwpi->proxyBypass));
        }
    }
    else TRACE("Proxy is disabled.\n");

    RegCloseKey( key );
    return ERROR_SUCCESS;
}