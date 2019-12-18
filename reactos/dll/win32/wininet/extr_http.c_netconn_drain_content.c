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
struct TYPE_4__ {unsigned int content_length; unsigned int content_read; } ;
typedef  TYPE_1__ netconn_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  netconn; } ;
typedef  TYPE_2__ http_request_t ;
typedef  int /*<<< orphan*/  data_stream_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int NETCON_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int*) ; 
 int WSAECONNABORTED ; 
 int WSAEISCONN ; 
 size_t min (int,unsigned int) ; 

__attribute__((used)) static DWORD netconn_drain_content(data_stream_t *stream, http_request_t *req, BOOL allow_blocking)
{
    netconn_stream_t *netconn_stream = (netconn_stream_t*)stream;
    BYTE buf[1024];
    int len, res;
    size_t size;

    if(netconn_stream->content_length == ~0u)
        return WSAEISCONN;

    while(netconn_stream->content_read < netconn_stream->content_length) {
        size = min(sizeof(buf), netconn_stream->content_length-netconn_stream->content_read);
        res = NETCON_recv(req->netconn, buf, size, allow_blocking, &len);
        if(res)
            return res;
        if(!len)
            return WSAECONNABORTED;

        netconn_stream->content_read += len;
    }

    return ERROR_SUCCESS;
}