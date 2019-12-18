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
struct route_gateway_info {char* iface; int /*<<< orphan*/  adapter_index; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_ROUTE ; 
 int LR_ERROR ; 
 int /*<<< orphan*/  M_FATAL ; 
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
 int /*<<< orphan*/  TUN_ADAPTER_INDEX_INVALID ; 
 int /*<<< orphan*/  WIN_ROUTE_PATH_SUFFIX ; 
 int add_route_ipapi (struct route_ipv4*,struct tuntap const*,int /*<<< orphan*/ ) ; 
 int add_route_service (struct route_ipv4*,struct tuntap const*) ; 
 int /*<<< orphan*/  argv_msg (int /*<<< orphan*/ ,struct argv*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,...) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 int /*<<< orphan*/  gc_init (struct gc_arena*) ; 
 int /*<<< orphan*/  get_win_sys_path () ; 
 scalar_t__ is_on_link (int,unsigned int,struct route_gateway_info const*) ; 
 int local_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct route_gateway_info const*) ; 
 int /*<<< orphan*/  management ; 
 int /*<<< orphan*/  management_android_control (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  net_ctx_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ net_route_v4_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netcmd_semaphore_lock () ; 
 int /*<<< orphan*/  netcmd_semaphore_release () ; 
 int netmask_to_netbits2 (int /*<<< orphan*/ ) ; 
 int openvpn_execve_check (struct argv*,struct env_set const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  openvpn_snprintf (char*,int,char*,char const*,char const*,char const*,...) ; 
 char* print_in_addr_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 

void
add_route(struct route_ipv4 *r,
          const struct tuntap *tt,
          unsigned int flags,
          const struct route_gateway_info *rgi,  /* may be NULL */
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
    const char *gateway;
#endif
    bool status = false;
    int is_local_route;

    if (!(r->flags & RT_DEFINED))
    {
        return;
    }

    gc_init(&gc);

#if !defined(TARGET_LINUX)
    network = print_in_addr_t(r->network, 0, &gc);
#if !defined(TARGET_AIX)
    netmask = print_in_addr_t(r->netmask, 0, &gc);
#endif
    gateway = print_in_addr_t(r->gateway, 0, &gc);
#endif

    is_local_route = local_route(r->network, r->netmask, r->gateway, rgi);
    if (is_local_route == LR_ERROR)
    {
        goto done;
    }

#if defined(TARGET_LINUX)
    const char *iface = NULL;
    int metric = -1;

    if (is_on_link(is_local_route, flags, rgi))
    {
        iface = rgi->iface;
    }

    if (r->flags & RT_METRIC_DEFINED)
    {
        metric = r->metric;
    }

    status = true;
    if (net_route_v4_add(ctx, &r->network, netmask_to_netbits2(r->netmask),
                         &r->gateway, iface, 0, metric) < 0)
    {
        msg(M_WARN, "ERROR: Linux route add command failed");
        status = false;
    }

#elif defined (TARGET_ANDROID)
    char out[128];

    if (rgi)
    {
        openvpn_snprintf(out, sizeof(out), "%s %s %s dev %s", network, netmask, gateway, rgi->iface);
    }
    else
    {
        openvpn_snprintf(out, sizeof(out), "%s %s %s", network, netmask, gateway);
    }
    management_android_control(management, "ROUTE", out);

#elif defined (_WIN32)
    {
        DWORD ai = TUN_ADAPTER_INDEX_INVALID;
        argv_printf(&argv, "%s%sc ADD %s MASK %s %s",
                    get_win_sys_path(),
                    WIN_ROUTE_PATH_SUFFIX,
                    network,
                    netmask,
                    gateway);
        if (r->flags & RT_METRIC_DEFINED)
        {
            argv_printf_cat(&argv, "METRIC %d", r->metric);
        }
        if (is_on_link(is_local_route, flags, rgi))
        {
            ai = rgi->adapter_index;
            argv_printf_cat(&argv, "IF %lu", ai);
        }

        argv_msg(D_ROUTE, &argv);

        if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_SERVICE)
        {
            status = add_route_service(r, tt);
            msg(D_ROUTE, "Route addition via service %s", status ? "succeeded" : "failed");
        }
        else if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_IPAPI)
        {
            status = add_route_ipapi(r, tt, ai);
            msg(D_ROUTE, "Route addition via IPAPI %s", status ? "succeeded" : "failed");
        }
        else if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_EXE)
        {
            netcmd_semaphore_lock();
            status = openvpn_execve_check(&argv, es, 0, "ERROR: Windows route add command failed");
            netcmd_semaphore_release();
        }
        else if ((flags & ROUTE_METHOD_MASK) == ROUTE_METHOD_ADAPTIVE)
        {
            status = add_route_ipapi(r, tt, ai);
            msg(D_ROUTE, "Route addition via IPAPI %s [adaptive]", status ? "succeeded" : "failed");
            if (!status)
            {
                msg(D_ROUTE, "Route addition fallback to route.exe");
                netcmd_semaphore_lock();
                status = openvpn_execve_check(&argv, es, 0, "ERROR: Windows route add command failed [adaptive]");
                netcmd_semaphore_release();
            }
        }
        else
        {
            ASSERT(0);
        }
    }

#elif defined (TARGET_SOLARIS)

    /* example: route add 192.0.2.32 -netmask 255.255.255.224 somegateway */

    argv_printf(&argv, "%s add",
                ROUTE_PATH);

    argv_printf_cat(&argv, "%s -netmask %s %s",
                    network,
                    netmask,
                    gateway);

    /* Solaris can only distinguish between "metric 0" == "on-link on the
     * interface where the IP address given is configured" and "metric > 0"
     * == "use gateway specified" (no finer-grained route metrics available)
     *
     * More recent versions of Solaris can also do "-interface", but that
     * would break backwards compatibility with older versions for no gain.
     */
    if (r->flags & RT_METRIC_DEFINED)
    {
        argv_printf_cat(&argv, "%d", r->metric);
    }

    argv_msg(D_ROUTE, &argv);
    status = openvpn_execve_check(&argv, es, 0, "ERROR: Solaris route add command failed");

#elif defined(TARGET_FREEBSD)

    argv_printf(&argv, "%s add",
                ROUTE_PATH);

#if 0
    if (r->flags & RT_METRIC_DEFINED)
    {
        argv_printf_cat(&argv, "-rtt %d", r->metric);
    }
#endif

    argv_printf_cat(&argv, "-net %s %s %s",
                    network,
                    gateway,
                    netmask);

    /* FIXME -- add on-link support for FreeBSD */

    argv_msg(D_ROUTE, &argv);
    status = openvpn_execve_check(&argv, es, 0, "ERROR: FreeBSD route add command failed");

#elif defined(TARGET_DRAGONFLY)

    argv_printf(&argv, "%s add",
                ROUTE_PATH);

#if 0
    if (r->flags & RT_METRIC_DEFINED)
    {
        argv_printf_cat(&argv, "-rtt %d", r->metric);
    }
#endif

    argv_printf_cat(&argv, "-net %s %s %s",
                    network,
                    gateway,
                    netmask);

    /* FIXME -- add on-link support for Dragonfly */

    argv_msg(D_ROUTE, &argv);
    status = openvpn_execve_check(&argv, es, 0, "ERROR: DragonFly route add command failed");

#elif defined(TARGET_DARWIN)

    argv_printf(&argv, "%s add",
                ROUTE_PATH);

#if 0
    if (r->flags & RT_METRIC_DEFINED)
    {
        argv_printf_cat(&argv, "-rtt %d", r->metric);
    }
#endif

    if (is_on_link(is_local_route, flags, rgi))
    {
        /* Mac OS X route syntax for ON_LINK:
         * route add -cloning -net 10.10.0.1 -netmask 255.255.255.255 -interface en0 */
        argv_printf_cat(&argv, "-cloning -net %s -netmask %s -interface %s",
                        network,
                        netmask,
                        rgi->iface);
    }
    else
    {
        argv_printf_cat(&argv, "-net %s %s %s",
                        network,
                        gateway,
                        netmask);
    }

    argv_msg(D_ROUTE, &argv);
    status = openvpn_execve_check(&argv, es, 0, "ERROR: OS X route add command failed");

#elif defined(TARGET_OPENBSD) || defined(TARGET_NETBSD)

    argv_printf(&argv, "%s add",
                ROUTE_PATH);

#if 0
    if (r->flags & RT_METRIC_DEFINED)
    {
        argv_printf_cat(&argv, "-rtt %d", r->metric);
    }
#endif

    argv_printf_cat(&argv, "-net %s %s -netmask %s",
                    network,
                    gateway,
                    netmask);

    /* FIXME -- add on-link support for OpenBSD/NetBSD */

    argv_msg(D_ROUTE, &argv);
    status = openvpn_execve_check(&argv, es, 0, "ERROR: OpenBSD/NetBSD route add command failed");

#elif defined(TARGET_AIX)

    {
        int netbits = netmask_to_netbits2(r->netmask);
        argv_printf(&argv, "%s add -net %s/%d %s",
                    ROUTE_PATH,
                    network, netbits, gateway);
        argv_msg(D_ROUTE, &argv);
        status = openvpn_execve_check(&argv, es, 0, "ERROR: AIX route add command failed");
    }

#else  /* if defined(TARGET_LINUX) */
    msg(M_FATAL, "Sorry, but I don't know how to do 'route' commands on this operating system.  Try putting your routes in a --route-up script");
#endif /* if defined(TARGET_LINUX) */

done:
    if (status)
    {
        r->flags |= RT_ADDED;
    }
    else
    {
        r->flags &= ~RT_ADDED;
    }
    argv_reset(&argv);
    gc_free(&gc);
    /* release resources potentially allocated during route setup */
    net_ctx_reset(ctx);
}