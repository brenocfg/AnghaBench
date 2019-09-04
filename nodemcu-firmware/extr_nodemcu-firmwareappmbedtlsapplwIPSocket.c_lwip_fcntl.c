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
struct TYPE_3__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ lwIP_sock ;

/* Variables and functions */
#define  F_GETFL 129 
#define  F_SETFL 128 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 TYPE_1__* get_socket (int) ; 
 int /*<<< orphan*/  netconn_is_nonblocking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netconn_set_nonblocking (int /*<<< orphan*/ ,int) ; 

int lwip_fcntl(int s, int cmd, int val)
{
    lwIP_sock *sock = get_socket(s);
    int ret = -1;

    if (!sock || !sock->conn)
    {
        return -1;
    }

    switch (cmd)
    {
        case F_GETFL:
            ret = netconn_is_nonblocking(sock->conn) ? O_NONBLOCK : 0;
            break;
        case F_SETFL:
            if ((val & ~O_NONBLOCK) == 0)
            {
                /* only O_NONBLOCK, all other bits are zero */
                netconn_set_nonblocking(sock->conn, val & O_NONBLOCK);
                ret = 0;
            }
            break;
        default:
            LWIP_DEBUGF(SOCKETS_DEBUG, ("lwip_fcntl(%d, UNIMPL: %d, %d)\n", s, cmd, val));
            break;
    }
    return ret;
}