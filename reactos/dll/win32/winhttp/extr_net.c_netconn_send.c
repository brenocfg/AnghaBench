#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cbMaximumMessage; } ;
struct TYPE_6__ {int /*<<< orphan*/  socket; TYPE_1__ ssl_sizes; scalar_t__ secure; } ;
typedef  TYPE_2__ netconn_t ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  errno ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ssl_chunk (TYPE_2__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_get_error (int /*<<< orphan*/ ) ; 
 int sock_send (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 

BOOL netconn_send( netconn_t *conn, const void *msg, size_t len, int *sent )
{
    if (conn->secure)
    {
        const BYTE *ptr = msg;
        size_t chunk_size;

        *sent = 0;

        while(len) {
            chunk_size = min(len, conn->ssl_sizes.cbMaximumMessage);
            if(!send_ssl_chunk(conn, ptr, chunk_size))
                return FALSE;

            *sent += chunk_size;
            ptr += chunk_size;
            len -= chunk_size;
        }

        return TRUE;
    }
    if ((*sent = sock_send( conn->socket, msg, len, 0 )) == -1)
    {
        set_last_error( sock_get_error( errno ) );
        return FALSE;
    }
    return TRUE;
}