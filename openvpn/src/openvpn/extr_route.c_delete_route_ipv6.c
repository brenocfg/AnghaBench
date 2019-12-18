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
struct TYPE_3__ {scalar_t__ msg_channel; } ;
struct tuntap {char* actual_name; scalar_t__ type; int /*<<< orphan*/  adapter_index; TYPE_1__ options; } ;
struct route_ipv6 {int flags; char* iface; int metric; int /*<<< orphan*/  netbits; int /*<<< orphan*/  gateway; int /*<<< orphan*/  adapter_index; int /*<<< orphan*/  network; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;
struct TYPE_4__ {char const* metric; } ;

/* Variables and functions */
 scalar_t__ DEV_TYPE_TAP ; 
 scalar_t__ DEV_TYPE_TUN ; 
 int /*<<< orphan*/  D_ROUTE ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  NETSH_PATH_SUFFIX ; 
 int /*<<< orphan*/  ROUTE_PATH ; 
 int RT_ADDED ; 
 int RT_DEFINED ; 
 int RT_METRIC_DEFINED ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  argv_msg (int /*<<< orphan*/ ,struct argv*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ,char const*,char const*,...) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,...) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 char* buf_bptr (struct buffer*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_route_ipv6_service (struct route_ipv6 const*,struct tuntap const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 int /*<<< orphan*/  gc_init (struct gc_arena*) ; 
 char* gc_malloc (int,int,struct gc_arena*) ; 
 int /*<<< orphan*/  get_win_sys_path () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  net_ctx_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ net_route_v6_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netcmd_semaphore_lock () ; 
 int /*<<< orphan*/  netcmd_semaphore_release () ; 
 int /*<<< orphan*/  openvpn_execve_check (struct argv*,struct env_set const*,int /*<<< orphan*/ ,char*) ; 
 char* print_in6_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 
 TYPE_2__* r ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

void
delete_route_ipv6(const struct route_ipv6 *r6, const struct tuntap *tt,
                  unsigned int flags, const struct env_set *es,
                  openvpn_net_ctx_t *ctx)
{
    struct gc_arena gc;
    struct argv argv = argv_new();
    const char *network;
#if !defined(TARGET_LINUX)
    const char *gateway;
#else
    int metric;
#endif
    const char *device = tt->actual_name;
    bool gateway_needed = false;

    if ((r6->flags & (RT_DEFINED|RT_ADDED)) != (RT_DEFINED|RT_ADDED))
    {
        return;
    }

#ifndef _WIN32
    if (r6->iface != NULL)              /* vpn server special route */
    {
        device = r6->iface;
        gateway_needed = true;
    }
#endif

    gc_init(&gc);

    network = print_in6_addr( r6->network, 0, &gc);
#if !defined(TARGET_LINUX)
    gateway = print_in6_addr( r6->gateway, 0, &gc);
#endif

#if defined(TARGET_DARWIN)    \
    || defined(TARGET_FREEBSD) || defined(TARGET_DRAGONFLY)    \
    || defined(TARGET_OPENBSD) || defined(TARGET_NETBSD)

    /* the BSD platforms cannot specify gateway and interface independently,
     * but for link-local destinations, we MUST specify the interface, so
     * we build a combined "$gateway%$interface" gateway string
     */
    if (r6->iface != NULL && gateway_needed
        && IN6_IS_ADDR_LINKLOCAL(&r6->gateway) )        /* fe80::...%intf */
    {
        int len = strlen(gateway) + 1 + strlen(r6->iface)+1;
        char *tmp = gc_malloc( len, true, &gc );
        snprintf( tmp, len, "%s%%%s", gateway, r6->iface );
        gateway = tmp;
    }
#endif

    msg( M_INFO, "delete_route_ipv6(%s/%d)", network, r6->netbits );

    /* if we used a gateway on "add route", we also need to specify it on
     * delete, otherwise some OSes will refuse to delete the route
     */
    if (tt->type == DEV_TYPE_TAP
        && !( (r6->flags & RT_METRIC_DEFINED) && r6->metric == 0 ) )
    {
        gateway_needed = true;
    }

#if defined(TARGET_LINUX)
    metric = -1;
    if ((r6->flags & RT_METRIC_DEFINED) && (r6->metric > 0))
    {
        metric = r6->metric;
    }

    if (net_route_v6_del(ctx, &r6->network, r6->netbits,
                         gateway_needed ? &r6->gateway : NULL, device, 0,
                         metric) < 0)
    {
        msg(M_WARN, "ERROR: Linux route v6 delete command failed");
    }

#elif defined (_WIN32)

    if (tt->options.msg_channel)
    {
        del_route_ipv6_service(r6, tt);
    }
    else
    {
        struct buffer out = alloc_buf_gc(64, &gc);
        if (r6->adapter_index)          /* vpn server special route */
        {
            buf_printf(&out, "interface=%lu", r6->adapter_index );
            gateway_needed = true;
        }
        else
        {
            buf_printf(&out, "interface=%lu", tt->adapter_index );
        }
        device = buf_bptr(&out);

        /* netsh interface ipv6 delete route 2001:db8::/32 MyTunDevice */
        argv_printf(&argv, "%s%sc interface ipv6 delete route %s/%d %s",
                    get_win_sys_path(),
                    NETSH_PATH_SUFFIX,
                    network,
                    r6->netbits,
                    device);

        /* next-hop depends on TUN or TAP mode:
         * - in TAP mode, we use the "real" next-hop
         * - in TUN mode we use a special-case link-local address that the tapdrvr
         *   knows about and will answer ND (neighbor discovery) packets for
         * (and "route deletion without specifying next-hop" does not work...)
         */
        if (tt->type == DEV_TYPE_TUN && !gateway_needed)
        {
            argv_printf_cat( &argv, " %s", "fe80::8" );
        }
        else if (!IN6_IS_ADDR_UNSPECIFIED(&r6->gateway) )
        {
            argv_printf_cat( &argv, " %s", gateway );
        }

#if 0
        if (r6->flags & RT_METRIC_DEFINED)
        {
            argv_printf_cat(&argv, "METRIC %d", r->metric);
        }
#endif

        /* Windows XP to 7 "just delete" routes, wherever they came from, but
         * in Windows 8(.1?), if you create them with "store=active", this is
         * how you should delete them as well (pointed out by Cedric Tabary)
         */
        argv_printf_cat( &argv, " store=active" );

        argv_msg(D_ROUTE, &argv);

        netcmd_semaphore_lock();
        openvpn_execve_check(&argv, es, 0, "ERROR: Windows route delete ipv6 command failed");
        netcmd_semaphore_release();
    }

#elif defined (TARGET_SOLARIS)

    /* example: route delete -inet6 2001:db8::/32 somegateway */

    argv_printf(&argv, "%s delete -inet6 %s/%d %s",
                ROUTE_PATH,
                network,
                r6->netbits,
                gateway );

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: Solaris route delete -inet6 command failed");

#elif defined(TARGET_FREEBSD) || defined(TARGET_DRAGONFLY)

    argv_printf(&argv, "%s delete -inet6 %s/%d",
                ROUTE_PATH,
                network,
                r6->netbits );

    if (gateway_needed)
    {
        argv_printf_cat(&argv, "%s", gateway);
    }
    else
    {
        argv_printf_cat(&argv, "-iface %s", device);
    }

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: *BSD route delete -inet6 command failed");

#elif defined(TARGET_DARWIN)

    argv_printf(&argv, "%s delete -inet6 %s -prefixlen %d",
                ROUTE_PATH,
                network, r6->netbits );

    if (gateway_needed)
    {
        argv_printf_cat(&argv, "%s", gateway);
    }
    else
    {
        argv_printf_cat(&argv, "-iface %s", device);
    }

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: MacOS X route delete -inet6 command failed");

#elif defined(TARGET_OPENBSD)

    argv_printf(&argv, "%s delete -inet6 %s -prefixlen %d %s",
                ROUTE_PATH,
                network, r6->netbits, gateway );

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: OpenBSD route delete -inet6 command failed");

#elif defined(TARGET_NETBSD)

    argv_printf(&argv, "%s delete -inet6 %s/%d %s",
                ROUTE_PATH,
                network, r6->netbits, gateway );

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: NetBSD route delete -inet6 command failed");

#elif defined(TARGET_AIX)

    argv_printf(&argv, "%s delete -inet6 %s/%d %s",
                ROUTE_PATH,
                network, r6->netbits, gateway);
    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: AIX route add command failed");

#else  /* if defined(TARGET_LINUX) */
    msg(M_FATAL, "Sorry, but I don't know how to do 'route ipv6' commands on this operating system.  Try putting your routes in a --route-down script");
#endif /* if defined(TARGET_LINUX) */

    argv_reset(&argv);
    gc_free(&gc);
    /* release resources potentially allocated during route cleanup */
    net_ctx_reset(ctx);
}