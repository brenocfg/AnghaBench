#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct link_socket {int /*<<< orphan*/  mark; void* sd; int /*<<< orphan*/  socket_buffer_sizes; void* ctrl_sd; scalar_t__ socks_proxy; int /*<<< orphan*/  sockflags; } ;
struct addrinfo {scalar_t__ ai_protocol; scalar_t__ ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  SF_GETADDRINFO_DGRAM ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  bind_local (struct link_socket*,int /*<<< orphan*/ ) ; 
 void* create_socket_tcp (struct addrinfo*) ; 
 void* create_socket_udp (struct addrinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_buffers (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_set_mark (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_socket(struct link_socket *sock, struct addrinfo *addr)
{
    if (addr->ai_protocol == IPPROTO_UDP || addr->ai_socktype == SOCK_DGRAM)
    {
        sock->sd = create_socket_udp(addr, sock->sockflags);
        sock->sockflags |= SF_GETADDRINFO_DGRAM;

        /* Assume that control socket and data socket to the socks proxy
         * are using the same IP family */
        if (sock->socks_proxy)
        {
            /* Construct a temporary addrinfo to create the socket,
             * currently resolve two remote addresses is not supported,
             * TODO: Rewrite the whole resolve_remote */
            struct addrinfo addrinfo_tmp = *addr;
            addrinfo_tmp.ai_socktype = SOCK_STREAM;
            addrinfo_tmp.ai_protocol = IPPROTO_TCP;
            sock->ctrl_sd = create_socket_tcp(&addrinfo_tmp);
        }
    }
    else if (addr->ai_protocol == IPPROTO_TCP || addr->ai_socktype == SOCK_STREAM)
    {
        sock->sd = create_socket_tcp(addr);
    }
    else
    {
        ASSERT(0);
    }
    /* set socket buffers based on --sndbuf and --rcvbuf options */
    socket_set_buffers(sock->sd, &sock->socket_buffer_sizes);

    /* set socket to --mark packets with given value */
    socket_set_mark(sock->sd, sock->mark);

    bind_local(sock, addr->ai_family);
}