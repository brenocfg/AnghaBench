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
struct TYPE_3__ {scalar_t__ read_size; scalar_t__ read_buf; int /*<<< orphan*/  netconn; scalar_t__ read_pos; } ;
typedef  TYPE_1__ http_request_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ NETCON_recv (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static DWORD read_more_data( http_request_t *req, int maxlen )
{
    DWORD res;
    int len;

    if (req->read_pos)
    {
        /* move existing data to the start of the buffer */
        if(req->read_size)
            memmove( req->read_buf, req->read_buf + req->read_pos, req->read_size );
        req->read_pos = 0;
    }

    if (maxlen == -1) maxlen = sizeof(req->read_buf);

    res = NETCON_recv( req->netconn, req->read_buf + req->read_size,
                       maxlen - req->read_size, TRUE, &len );
    if(res == ERROR_SUCCESS)
        req->read_size += len;

    return res;
}