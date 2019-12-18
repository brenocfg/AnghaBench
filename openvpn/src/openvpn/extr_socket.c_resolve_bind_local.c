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
struct TYPE_4__ {TYPE_1__* lsa; int /*<<< orphan*/  proto; } ;
struct link_socket {int /*<<< orphan*/  local_port; int /*<<< orphan*/  local_host; TYPE_2__ info; int /*<<< orphan*/  dns_cache; } ;
struct gc_arena {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_3__ {int /*<<< orphan*/  bind_local; } ;

/* Variables and functions */
 int GETADDR_DATAGRAM ; 
 int GETADDR_FATAL ; 
 int GETADDR_PASSIVE ; 
 int GETADDR_RESOLVE ; 
 int GETADDR_WARN_ON_SIGNAL ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int get_cached_dns_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int openvpn_getaddrinfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 scalar_t__ proto_is_dgram (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resolve_bind_local(struct link_socket *sock, const sa_family_t af)
{
    struct gc_arena gc = gc_new();

    /* resolve local address if undefined */
    if (!sock->info.lsa->bind_local)
    {
        int flags = GETADDR_RESOLVE | GETADDR_WARN_ON_SIGNAL
                    |GETADDR_FATAL | GETADDR_PASSIVE;
        int status;

        if (proto_is_dgram(sock->info.proto))
        {
            flags |= GETADDR_DATAGRAM;
        }

        /* will return AF_{INET|INET6}from local_host */
        status = get_cached_dns_entry(sock->dns_cache,
                                      sock->local_host,
                                      sock->local_port,
                                      af,
                                      flags,
                                      &sock->info.lsa->bind_local);

        if (status)
        {
            status = openvpn_getaddrinfo(flags, sock->local_host, sock->local_port, 0,
                                         NULL, af, &sock->info.lsa->bind_local);
        }

        if (status !=0)
        {
            msg(M_FATAL, "getaddrinfo() failed for local \"%s:%s\": %s",
                sock->local_host, sock->local_port,
                gai_strerror(status));
        }
    }

    gc_free(&gc);
}