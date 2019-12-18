#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int dwFlags; int dwInternalFlags; int /*<<< orphan*/  hInternet; int /*<<< orphan*/  entry; int /*<<< orphan*/  decoding; int /*<<< orphan*/  dwContext; int /*<<< orphan*/  htype; } ;
struct TYPE_10__ {TYPE_1__ hdr; scalar_t__ receive_timeout; scalar_t__ send_timeout; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  hostPort; void* password; void* userName; void* hostName; TYPE_3__* appInfo; } ;
typedef  TYPE_2__ http_session_t ;
struct TYPE_12__ {scalar_t__ htype; int /*<<< orphan*/  children; int /*<<< orphan*/  decoding; } ;
struct TYPE_11__ {TYPE_5__ hdr; int /*<<< orphan*/  connect_timeout; } ;
typedef  TYPE_3__ appinfo_t ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  INTERNET_PORT ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_OUTOFMEMORY ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  HTTPSESSIONVtbl ; 
 int INET_OPENURL ; 
 int /*<<< orphan*/  INTERNET_STATUS_HANDLE_CREATED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WH_HHTTPSESSION ; 
 scalar_t__ WH_HINIT ; 
 int /*<<< orphan*/  WININET_AddRef (TYPE_5__*) ; 
 TYPE_2__* alloc_object (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* heap_strdupW (scalar_t__*) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DWORD HTTP_Connect(appinfo_t *hIC, LPCWSTR lpszServerName,
        INTERNET_PORT serverPort, LPCWSTR lpszUserName,
        LPCWSTR lpszPassword, DWORD dwFlags, DWORD_PTR dwContext,
        DWORD dwInternalFlags, HINTERNET *ret)
{
    http_session_t *session = NULL;

    TRACE("-->\n");

    if (!lpszServerName || !lpszServerName[0])
        return ERROR_INVALID_PARAMETER;

    assert( hIC->hdr.htype == WH_HINIT );

    session = alloc_object(&hIC->hdr, &HTTPSESSIONVtbl, sizeof(http_session_t));
    if (!session)
        return ERROR_OUTOFMEMORY;

   /*
    * According to my tests. The name is not resolved until a request is sent
    */

    session->hdr.htype = WH_HHTTPSESSION;
    session->hdr.dwFlags = dwFlags;
    session->hdr.dwContext = dwContext;
    session->hdr.dwInternalFlags |= dwInternalFlags;
    session->hdr.decoding = hIC->hdr.decoding;

    WININET_AddRef( &hIC->hdr );
    session->appInfo = hIC;
    list_add_head( &hIC->hdr.children, &session->hdr.entry );

    session->hostName = heap_strdupW(lpszServerName);
    if (lpszUserName && lpszUserName[0])
        session->userName = heap_strdupW(lpszUserName);
    if (lpszPassword && lpszPassword[0])
        session->password = heap_strdupW(lpszPassword);
    session->hostPort = serverPort;
    session->connect_timeout = hIC->connect_timeout;
    session->send_timeout = 0;
    session->receive_timeout = 0;

    /* Don't send a handle created callback if this handle was created with InternetOpenUrl */
    if (!(session->hdr.dwInternalFlags & INET_OPENURL))
    {
        INTERNET_SendCallback(&hIC->hdr, dwContext,
                              INTERNET_STATUS_HANDLE_CREATED, &session->hdr.hInternet,
                              sizeof(HINTERNET));
    }

/*
 * an INTERNET_STATUS_REQUEST_COMPLETE is NOT sent here as per my tests on
 * windows
 */

    TRACE("%p --> %p\n", hIC, session);

    *ret = session->hdr.hInternet;
    return ERROR_SUCCESS;
}