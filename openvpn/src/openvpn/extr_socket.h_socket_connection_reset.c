#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ error; } ;
struct link_socket {TYPE_1__ stream_buf; scalar_t__ stream_reset; } ;

/* Variables and functions */
 int const ECONNRESET ; 
 int const WSAECONNABORTED ; 
 int const WSAECONNRESET ; 
 scalar_t__ link_socket_connection_oriented (struct link_socket const*) ; 
 int openvpn_errno () ; 

__attribute__((used)) static inline bool
socket_connection_reset(const struct link_socket *sock, int status)
{
    if (link_socket_connection_oriented(sock))
    {
        if (sock->stream_reset || sock->stream_buf.error)
        {
            return true;
        }
        else if (status < 0)
        {
            const int err = openvpn_errno();
#ifdef _WIN32
            return err == WSAECONNRESET || err == WSAECONNABORTED;
#else
            return err == ECONNRESET;
#endif
        }
    }
    return false;
}