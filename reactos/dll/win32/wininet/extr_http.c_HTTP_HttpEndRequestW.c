#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int dwFlags; int /*<<< orphan*/  dwContext; } ;
struct TYPE_18__ {int status_code; scalar_t__ contentLength; int /*<<< orphan*/ * verb; TYPE_9__ hdr; int /*<<< orphan*/  netconn; } ;
typedef  TYPE_1__ http_request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_HTTP_HEADER_NOT_FOUND ; 
 scalar_t__ ERROR_INTERNET_OPERATION_CANCELLED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HTTP_GetResponseHeaders (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ HTTP_HandleRedirect (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ HTTP_HttpSendRequestW (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HTTP_ProcessCookies (TYPE_1__*) ; 
 int /*<<< orphan*/  HTTP_ProcessExpires (TYPE_1__*) ; 
 int /*<<< orphan*/  HTTP_ProcessLastModified (TYPE_1__*) ; 
 int /*<<< orphan*/  HTTP_ReceiveRequestData (TYPE_1__*) ; 
#define  HTTP_STATUS_MOVED 131 
#define  HTTP_STATUS_REDIRECT 130 
#define  HTTP_STATUS_REDIRECT_KEEP_VERB 129 
#define  HTTP_STATUS_REDIRECT_METHOD 128 
 int INTERNET_FLAG_NO_AUTO_REDIRECT ; 
 int /*<<< orphan*/  INTERNET_STATUS_RECEIVING_RESPONSE ; 
 int /*<<< orphan*/  INTERNET_STATUS_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  create_cache_entry (TYPE_1__*) ; 
 scalar_t__ drain_content (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_redirect_url (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_process_keep_alive (TYPE_1__*) ; 
 int /*<<< orphan*/  http_release_netconn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  is_valid_netconn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_complete (TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ set_content_length (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szGET ; 
 int /*<<< orphan*/  szHEAD ; 

__attribute__((used)) static DWORD HTTP_HttpEndRequestW(http_request_t *request, DWORD dwFlags, DWORD_PTR dwContext)
{
    INT responseLen;
    DWORD res = ERROR_SUCCESS;

    if(!is_valid_netconn(request->netconn)) {
        WARN("Not connected\n");
        send_request_complete(request, 0, ERROR_INTERNET_OPERATION_CANCELLED);
        return ERROR_INTERNET_OPERATION_CANCELLED;
    }

    INTERNET_SendCallback(&request->hdr, request->hdr.dwContext,
                  INTERNET_STATUS_RECEIVING_RESPONSE, NULL, 0);

    if (HTTP_GetResponseHeaders(request, &responseLen) || !responseLen)
        res = ERROR_HTTP_HEADER_NOT_FOUND;

    INTERNET_SendCallback(&request->hdr, request->hdr.dwContext,
                  INTERNET_STATUS_RESPONSE_RECEIVED, &responseLen, sizeof(DWORD));

    /* process cookies here. Is this right? */
    http_process_keep_alive(request);
    HTTP_ProcessCookies(request);
    HTTP_ProcessExpires(request);
    HTTP_ProcessLastModified(request);

    if ((res = set_content_length(request)) == ERROR_SUCCESS) {
        if(!request->contentLength)
            http_release_netconn(request, TRUE);
    }

    if (res == ERROR_SUCCESS && !(request->hdr.dwFlags & INTERNET_FLAG_NO_AUTO_REDIRECT))
    {
        switch(request->status_code) {
        case HTTP_STATUS_REDIRECT:
        case HTTP_STATUS_MOVED:
        case HTTP_STATUS_REDIRECT_METHOD:
        case HTTP_STATUS_REDIRECT_KEEP_VERB: {
            WCHAR *new_url;

            new_url = get_redirect_url(request);
            if(!new_url)
                break;

            if (strcmpW(request->verb, szGET) && strcmpW(request->verb, szHEAD) &&
                request->status_code != HTTP_STATUS_REDIRECT_KEEP_VERB)
            {
                heap_free(request->verb);
                request->verb = heap_strdupW(szGET);
            }
            http_release_netconn(request, drain_content(request, FALSE) == ERROR_SUCCESS);
            res = HTTP_HandleRedirect(request, new_url);
            heap_free(new_url);
            if (res == ERROR_SUCCESS)
                res = HTTP_HttpSendRequestW(request, NULL, 0, NULL, 0, 0, TRUE);
        }
        }
    }

    if(res == ERROR_SUCCESS)
        create_cache_entry(request);

    if (res == ERROR_SUCCESS && request->contentLength)
        HTTP_ReceiveRequestData(request);
    else
        send_request_complete(request, res == ERROR_SUCCESS, res);

    return res;
}