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
struct link_socket_actual {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;
struct link_socket {TYPE_1__ info; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int link_socket_write_tcp (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 int link_socket_write_udp (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 scalar_t__ proto_is_tcp (int /*<<< orphan*/ ) ; 
 scalar_t__ proto_is_udp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
link_socket_write(struct link_socket *sock,
                  struct buffer *buf,
                  struct link_socket_actual *to)
{
    if (proto_is_udp(sock->info.proto)) /* unified UDPv4 and UDPv6 */
    {
        return link_socket_write_udp(sock, buf, to);
    }
    else if (proto_is_tcp(sock->info.proto)) /* unified TCPv4 and TCPv6 */
    {
        return link_socket_write_tcp(sock, buf, to);
    }
    else
    {
        ASSERT(0);
        return -1; /* NOTREACHED */
    }
}