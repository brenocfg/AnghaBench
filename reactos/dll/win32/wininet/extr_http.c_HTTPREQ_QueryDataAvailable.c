#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ dwError; } ;
typedef  TYPE_4__ object_header_t ;
struct TYPE_12__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_17__ {int read_size; TYPE_10__ hdr; int /*<<< orphan*/  read_section; TYPE_3__* session; } ;
typedef  TYPE_5__ http_request_t ;
typedef  int /*<<< orphan*/  avail ;
struct TYPE_15__ {TYPE_2__* appInfo; } ;
struct TYPE_13__ {int dwFlags; } ;
struct TYPE_14__ {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INTERNET_INTERNAL_ERROR ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int INTERNET_FLAG_ASYNC ; 
 scalar_t__ INTERNET_HANDLE_IN_USE ; 
 int /*<<< orphan*/  INTERNET_STATUS_RECEIVING_RESPONSE ; 
 int /*<<< orphan*/  INTERNET_STATUS_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int IRF_ASYNC ; 
 int IRF_NO_WAIT ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_5__*,int*,int,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ TryEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int WSAEWOULDBLOCK ; 
 int async_read (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  end_of_read_data (TYPE_5__*) ; 
 int refill_read_buffer (TYPE_5__*,int,int*) ; 

__attribute__((used)) static DWORD HTTPREQ_QueryDataAvailable(object_header_t *hdr, DWORD *available, DWORD flags, DWORD_PTR ctx)
{
    http_request_t *req = (http_request_t*)hdr;
    DWORD res = ERROR_SUCCESS, avail = 0, error = ERROR_SUCCESS;
    BOOL allow_blocking, notify_received = FALSE;

    TRACE("(%p %p %x %lx)\n", req, available, flags, ctx);

    if (flags & ~(IRF_ASYNC|IRF_NO_WAIT))
        FIXME("these dwFlags aren't implemented: 0x%x\n", flags & ~(IRF_ASYNC|IRF_NO_WAIT));

    *available = 0;
    allow_blocking = !(req->session->appInfo->hdr.dwFlags & INTERNET_FLAG_ASYNC);

    if(allow_blocking || TryEnterCriticalSection(&req->read_section)) {
        if(allow_blocking)
            EnterCriticalSection(&req->read_section);
        if(hdr->dwError == ERROR_SUCCESS)
            hdr->dwError = INTERNET_HANDLE_IN_USE;
        else if(hdr->dwError == INTERNET_HANDLE_IN_USE)
            hdr->dwError = ERROR_INTERNET_INTERNAL_ERROR;

        avail = req->read_size;

        if(!avail && !end_of_read_data(req)) {
            LeaveCriticalSection(&req->read_section);
            INTERNET_SendCallback(&req->hdr, req->hdr.dwContext, INTERNET_STATUS_RECEIVING_RESPONSE, NULL, 0);
            EnterCriticalSection( &req->read_section );
            notify_received = TRUE;

            res = refill_read_buffer(req, allow_blocking, &avail);
        }

        if(hdr->dwError == INTERNET_HANDLE_IN_USE)
            hdr->dwError = ERROR_SUCCESS;
        else
            error = hdr->dwError;

        LeaveCriticalSection( &req->read_section );
    }else {
        res = WSAEWOULDBLOCK;
    }

    if(res == WSAEWOULDBLOCK)
        return async_read(req, NULL, 0, 0, available);

    if (res != ERROR_SUCCESS)
        return res;

    *available = avail;
    if(notify_received)
        INTERNET_SendCallback(&req->hdr, req->hdr.dwContext, INTERNET_STATUS_RESPONSE_RECEIVED,
                &avail, sizeof(avail));
    return error;
}