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
typedef  int /*<<< orphan*/  v6only ;
struct gc_arena {int dummy; } ;
struct addrinfo {int ai_family; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_addrlen; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  socket_descriptor_t ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/  ASSERT (struct addrinfo*) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int M_ERRNO ; 
 int M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 int M_NONFATAL ; 
 int /*<<< orphan*/  PS_SHOW_PORT ; 
 int /*<<< orphan*/  addr_family_name (int) ; 
 scalar_t__ bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  print_sockaddr_ex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct gc_arena*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

void
socket_bind(socket_descriptor_t sd,
            struct addrinfo *local,
            int ai_family,
            const char *prefix,
            bool ipv6only)
{
    struct gc_arena gc = gc_new();

    /* FIXME (schwabe)
     * getaddrinfo for the bind address might return multiple AF_INET/AF_INET6
     * entries for the requested protocol.
     * For example if an address has multiple A records
     * What is the correct way to deal with it?
     */

    struct addrinfo *cur;

    ASSERT(local);


    /* find the first addrinfo with correct ai_family */
    for (cur = local; cur; cur = cur->ai_next)
    {
        if (cur->ai_family == ai_family)
        {
            break;
        }
    }
    if (!cur)
    {
        msg(M_FATAL, "%s: Socket bind failed: Addr to bind has no %s record",
            prefix, addr_family_name(ai_family));
    }

    if (ai_family == AF_INET6)
    {
        int v6only = ipv6only ? 1 : 0;  /* setsockopt must have an "int" */

        msg(M_INFO, "setsockopt(IPV6_V6ONLY=%d)", v6only);
        if (setsockopt(sd, IPPROTO_IPV6, IPV6_V6ONLY, (void *) &v6only, sizeof(v6only)))
        {
            msg(M_NONFATAL|M_ERRNO, "Setting IPV6_V6ONLY=%d failed", v6only);
        }
    }
    if (bind(sd, cur->ai_addr, cur->ai_addrlen))
    {
        msg(M_FATAL | M_ERRNO, "%s: Socket bind failed on local address %s",
            prefix,
            print_sockaddr_ex(local->ai_addr, ":", PS_SHOW_PORT, &gc));
    }
    gc_free(&gc);
}