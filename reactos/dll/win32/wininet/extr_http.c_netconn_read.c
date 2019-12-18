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
struct TYPE_4__ {scalar_t__ content_read; scalar_t__ content_length; } ;
typedef  TYPE_1__ netconn_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  netconn; } ;
typedef  TYPE_2__ http_request_t ;
typedef  int /*<<< orphan*/  data_stream_t ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ NETCON_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int) ; 
 scalar_t__ is_valid_netconn (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static DWORD netconn_read(data_stream_t *stream, http_request_t *req, BYTE *buf, DWORD size,
        DWORD *read, BOOL allow_blocking)
{
    netconn_stream_t *netconn_stream = (netconn_stream_t*)stream;
    DWORD res = ERROR_SUCCESS;
    int ret = 0;

    size = min(size, netconn_stream->content_length-netconn_stream->content_read);

    if(size && is_valid_netconn(req->netconn)) {
        res = NETCON_recv(req->netconn, buf, size, allow_blocking, &ret);
        if(res == ERROR_SUCCESS) {
            if(!ret)
                netconn_stream->content_length = netconn_stream->content_read;
            netconn_stream->content_read += ret;
        }
    }

    TRACE("res %u read %u bytes\n", res, ret);
    *read = ret;
    return res;
}