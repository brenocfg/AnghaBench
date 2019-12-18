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
struct tuntap {int dummy; } ;
struct route_ipv4 {int flags; int metric; int /*<<< orphan*/  netmask; int /*<<< orphan*/  gateway; int /*<<< orphan*/  network; } ;
struct route_gateway_info {int /*<<< orphan*/  iface; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_ROUTE ; 
 int LR_ERROR ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_NONFATAL ; 
 int /*<<< orphan*/  M_WARN ; 
 unsigned int ROUTE_METHOD_ADAPTIVE ; 
 unsigned int ROUTE_METHOD_EXE ; 
 unsigned int ROUTE_METHOD_IPAPI ; 
 unsigned int ROUTE_METHOD_MASK ; 
 unsigned int ROUTE_METHOD_SERVICE ; 
 int /*<<< orphan*/  ROUTE_PATH ; 
 int RT_ADDED ; 
 int RT_DEFINED ; 
 int RT_METRIC_DEFINED ; 
 int /*<<< orphan*/  WIN_ROUTE_PATH_SUFFIX ; 
 int /*<<< orphan*/  argv_msg (int /*<<< orphan*/ ,struct argv*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int del_route_ipapi (struct route_ipv4*,struct tuntap const*) ; 
 int del_route_service (struct route_ipv4*,struct tuntap const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 int /*<<< orphan*/  gc_init (struct gc_arena*) ; 
 int /*<<< orphan*/  get_win_sys_path () ; 
 scalar_t__ is_on_link (int,unsigned int,struct route_gateway_info const*) ; 
 int local_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct route_gateway_info const*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  net_ctx_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ net_route_v4_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netcmd_semaphore_lock () ; 
 int /*<<< orphan*/  netcmd_semaphore_release () ; 
 int netmask_to_netbits2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openvpn_execve_check (struct argv*,struct env_set const*,int /*<<< orphan*/ ,char*) ; 
 char* print_in_addr_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 

__attribute__((used)) static void
delete_route(struct route_ipv4 *r,
             const struct tuntap *tt,
             unsigned int flags,
             const struct route_gateway_info *rgi,
             const struct env_set *es,
             openvpn_net_ctx_t *ctx)
{
    struct gc_arena gc;
    struct argv argv = argv_new();
#if !defined(TARGET_LINUX)
    const char *network;
#if !defined(TARGET_AIX)
    const char *netmask;
#endif
#if !defined(TARGET_ANDROID)
    const char *gateway;
#endif
#else
    int metric;
#endif
    int is_local_route;

    if ((r->flags & (RT_DEFINED|RT_ADDED)) != (RT_DEFINED|RT_ADDED))
    {
        return;
    }

    gc_init(&gc);

#if !defined(TARGET_LINUX)
    network = print_in_addr_t(r->network, 0, &gc);
#if !defined(TARGET_AIX)
    netmask = print_in_addr_t(r->netmask, 0, &gc);
#endif
#if !defined(TARGET_ANDROID)
    gateway = print_in_addr_t(r->gateway, 0, &gc);
#endif
#endif

    is_local_route = local_route(r->network, r->netmask, r->gateway, rgi);
    if (is_local_route == LR_ERROR)
    {
        goto done;
    }

#if defined(TARGET_LINUX)
    metric = -1;
    if (r->flags & RT_METRIC_DEFINED)
    {
        metric = r->metric;
    }

    if (net_route_v4_del(ctx, &r->network, netmask_to_netbits2(r->netmask),
                         &r->gateway, NULL, 0, metric) < 0)
    {
        msg(M_WARN, "ERROR: Linux route delete command failed");
    }
#elif defined (_WIN32)

    argv_printf(&argv, "%s%sc DELETE %s MASK %s %s",
                get_win_sys_path(),
                WIN_ROUTE_PATH_SUFFIX,
                network,
                netmask,
                gateway);

    argv_msg(D_ROUTE, &argv);

    if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_SERVICE)
    {
        const bool status = del_route_service(r, tt);
        msg(D_ROUTE, "Route deletion via service %s", status ? "succeeded" : "failed");
    }
    else if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_IPAPI)
    {
        const bool status = del_route_ipapi(r, tt);
        msg(D_ROUTE, "Route deletion via IPAPI %s", status ? "succeeded" : "failed");
    }
    else if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_EXE)
    {
        netcmd_semaphore_lock();
        openvpn_execve_check(&argv, es, 0, "ERROR: Windows route delete command failed");
        netcmd_semaphore_release();
    }
    else if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_ADAPTIVE)
    {
        const bool status = del_route_ipapi(r, tt);
        msg(D_ROUTE, "Route deletion via IPAPI %s [adaptive]", status ? "succeeded" : "failed");
        if (!status)
        {
            msg(D_ROUTE, "Route deletion fallback to route.exe");
            netcmd_semaphore_lock();
            openvpn_execve_check(&argv, es, 0, "ERROR: Windows route delete command failed [adaptive]");
            netcmd_semaphore_release();
        }
    }
    else
    {
        ASSERT(0);
    }

#elif defined (TARGET_SOLARIS)

    argv_printf(&argv, "%s delete %s -netmask %s %s",
                ROUTE_PATH,
                network,
                netmask,
                gateway);

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: Solaris route delete command failed");

#elif defined(TARGET_FREEBSD)

    argv_printf(&argv, "%s delete -net %s %s %s",
                ROUTE_PATH,
                network,
                gateway,
                netmask);

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: FreeBSD route delete command failed");

#elif defined(TARGET_DRAGONFLY)

    argv_printf(&argv, "%s delete -net %s %s %s",
                ROUTE_PATH,
                network,
                gateway,
                netmask);

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: DragonFly route delete command failed");

#elif defined(TARGET_DARWIN)

    if (is_on_link(is_local_route, flags, rgi))
    {
        argv_printf(&argv, "%s delete -cloning -net %s -netmask %s -interface %s",
                    ROUTE_PATH,
                    network,
                    netmask,
                    rgi->iface);
    }
    else
    {
        argv_printf(&argv, "%s delete -net %s %s %s",
                    ROUTE_PATH,
                    network,
                    gateway,
                    netmask);
    }

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: OS X route delete command failed");

#elif defined(TARGET_OPENBSD) || defined(TARGET_NETBSD)

    argv_printf(&argv, "%s delete -net %s %s -netmask %s",
                ROUTE_PATH,
                network,
                gateway,
                netmask);

    argv_msg(D_ROUTE, &argv);
    openvpn_execve_check(&argv, es, 0, "ERROR: OpenBSD/NetBSD route delete command failed");

#elif defined(TARGET_ANDROID)
    msg(M_NONFATAL, "Sorry, deleting routes on Android is not possible. The VpnService API allows routes to be set on connect only.");

#elif defined(TARGET_AIX)

    {
        int netbits = netmask_to_netbits2(r->netmask);
        argv_printf(&argv, "%s delete -net %s/%d %s",
                    ROUTE_PATH,
                    network, netbits, gateway);
        argv_msg(D_ROUTE, &argv);
        openvpn_execve_check(&argv, es, 0, "ERROR: AIX route delete command failed");
    }

#else  /* if defined(TARGET_LINUX) */
    msg(M_FATAL, "Sorry, but I don't know how to do 'route' commands on this operating system.  Try putting your routes in a --route-up script");
#endif /* if defined(TARGET_LINUX) */

done:
    r->flags &= ~RT_ADDED;
    argv_reset(&argv);
    gc_free(&gc);
    /* release resources potentially allocated during route cleanup */
    net_ctx_reset(ctx);
}