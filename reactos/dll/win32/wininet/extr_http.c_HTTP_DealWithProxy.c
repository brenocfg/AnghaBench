#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szHttp ;
struct TYPE_9__ {int /*<<< orphan*/  port; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ server_t ;
typedef  int /*<<< orphan*/  http_session_t ;
struct TYPE_10__ {char* path; TYPE_1__* proxy; } ;
typedef  TYPE_2__ http_request_t ;
struct TYPE_11__ {int /*<<< orphan*/  proxy; } ;
typedef  TYPE_3__ appinfo_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UrlComponents ;
struct TYPE_12__ {int member_0; int dwHostNameLength; scalar_t__ nScheme; int /*<<< orphan*/  nPort; int /*<<< orphan*/  lpszHostName; } ;
typedef  TYPE_4__ URL_COMPONENTSW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 char* INTERNET_FindProxyForProtocol (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ INTERNET_SCHEME_HTTPS ; 
 scalar_t__ InternetCrackUrlW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  strcatW (char*,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 
 int /*<<< orphan*/  substr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL HTTP_DealWithProxy(appinfo_t *hIC, http_session_t *session, http_request_t *request)
{
    static const WCHAR protoHttp[] = { 'h','t','t','p',0 };
    static const WCHAR szHttp[] = { 'h','t','t','p',':','/','/',0 };
    static WCHAR szNul[] = { 0 };
    URL_COMPONENTSW UrlComponents = { sizeof(UrlComponents) };
    server_t *new_server = NULL;
    WCHAR *proxy;

    proxy = INTERNET_FindProxyForProtocol(hIC->proxy, protoHttp);
    if(!proxy)
        return FALSE;
    if(CSTR_EQUAL != CompareStringW(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE,
                                    proxy, strlenW(szHttp), szHttp, strlenW(szHttp))) {
        WCHAR *proxy_url = heap_alloc(strlenW(proxy)*sizeof(WCHAR) + sizeof(szHttp));
        if(!proxy_url) {
            heap_free(proxy);
            return FALSE;
        }
        strcpyW(proxy_url, szHttp);
        strcatW(proxy_url, proxy);
        heap_free(proxy);
        proxy = proxy_url;
    }

    UrlComponents.dwHostNameLength = 1;
    if(InternetCrackUrlW(proxy, 0, 0, &UrlComponents) && UrlComponents.dwHostNameLength) {
        if( !request->path )
            request->path = szNul;

        new_server = get_server(substr(UrlComponents.lpszHostName, UrlComponents.dwHostNameLength),
                                UrlComponents.nPort, UrlComponents.nScheme == INTERNET_SCHEME_HTTPS, TRUE);
    }
    heap_free(proxy);
    if(!new_server)
        return FALSE;

    request->proxy = new_server;

    TRACE("proxy server=%s port=%d\n", debugstr_w(new_server->name), new_server->port);
    return TRUE;
}