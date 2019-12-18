#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  object_header_t ;
struct TYPE_4__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_3__ {TYPE_2__ hdr; int /*<<< orphan*/  bytesWritten; int /*<<< orphan*/  netconn; } ;
typedef  TYPE_1__ http_request_t ;
typedef  int /*<<< orphan*/  LPINT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  INTERNET_STATUS_REQUEST_SENT ; 
 int /*<<< orphan*/  INTERNET_STATUS_SENDING_REQUEST ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ NETCON_send (int /*<<< orphan*/ ,void const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD HTTPREQ_WriteFile(object_header_t *hdr, const void *buffer, DWORD size, DWORD *written)
{
    DWORD res;
    http_request_t *request = (http_request_t*)hdr;

    INTERNET_SendCallback(&request->hdr, request->hdr.dwContext, INTERNET_STATUS_SENDING_REQUEST, NULL, 0);

    *written = 0;
    res = NETCON_send(request->netconn, buffer, size, 0, (LPINT)written);
    if (res == ERROR_SUCCESS)
        request->bytesWritten += *written;

    INTERNET_SendCallback(&request->hdr, request->hdr.dwContext, INTERNET_STATUS_REQUEST_SENT, written, sizeof(DWORD));
    return res;
}