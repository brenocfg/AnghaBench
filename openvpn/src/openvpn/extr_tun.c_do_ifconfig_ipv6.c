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
struct TYPE_2__ {scalar_t__ ip_win32_type; int /*<<< orphan*/  dns6_len; int /*<<< orphan*/  dns6; scalar_t__ msg_channel; } ;
struct tuntap {char const* netbits_ipv6; scalar_t__ type; TYPE_1__ options; int /*<<< orphan*/  adapter_index; int /*<<< orphan*/  remote_ipv6; int /*<<< orphan*/  local_ipv6; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  out6 ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;
typedef  int /*<<< orphan*/  iface ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ DEV_TYPE_TUN ; 
 int /*<<< orphan*/  IFCONFIG_PATH ; 
 scalar_t__ IPW32_SET_MANUAL ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 char const* NETSH_PATH_SUFFIX ; 
 int /*<<< orphan*/  S_FATAL ; 
 int /*<<< orphan*/  add_route_connected_v6_net (struct tuntap*,struct env_set const*) ; 
 int /*<<< orphan*/  argv_msg (int /*<<< orphan*/ ,struct argv*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  do_address_service (int,int /*<<< orphan*/ ,struct tuntap*) ; 
 int /*<<< orphan*/  do_dns6_service (int,struct tuntap*) ; 
 int /*<<< orphan*/  env_set_add (struct env_set const*,char*) ; 
 struct env_set* env_set_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  env_set_destroy (struct env_set const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  get_win_sys_path () ; 
 int /*<<< orphan*/  management ; 
 int /*<<< orphan*/  management_android_control (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ net_addr_v6_add (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ net_iface_mtu_set (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ net_iface_up (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  netsh_command (struct argv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netsh_set_dns6_servers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  openvpn_execve_check (struct argv*,struct env_set const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  openvpn_snprintf (char*,int,char*,char const*,...) ; 
 char* print_in6_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  solaris_error_close (struct tuntap*,struct env_set const*,char const*,int) ; 

__attribute__((used)) static void
do_ifconfig_ipv6(struct tuntap *tt, const char *ifname, int tun_mtu,
                 const struct env_set *es, openvpn_net_ctx_t *ctx)
{
#if !defined(TARGET_LINUX)
    struct argv argv = argv_new();
    struct gc_arena gc = gc_new();
    const char *ifconfig_ipv6_local = print_in6_addr(tt->local_ipv6, 0, &gc);
#endif

#if defined(TARGET_LINUX)
    if (net_iface_mtu_set(ctx, ifname, tun_mtu) < 0)
    {
        msg(M_FATAL, "Linux can't set mtu (%d) on %s", tun_mtu, ifname);
    }

    if (net_iface_up(ctx, ifname, true) < 0)
    {
        msg(M_FATAL, "Linux can't bring %s up", ifname);
    }

    if (net_addr_v6_add(ctx, ifname, &tt->local_ipv6,
                        tt->netbits_ipv6) < 0)
    {
        msg(M_FATAL, "Linux can't add IPv6 to interface %s", ifname);
    }
#elif defined(TARGET_ANDROID)
    char out6[64];

    openvpn_snprintf(out6, sizeof(out6), "%s/%d %d",
                     ifconfig_ipv6_local, tt->netbits_ipv6, tun_mtu);
    management_android_control(management, "IFCONFIG6", out6);
#elif defined(TARGET_SOLARIS)
    argv_printf(&argv, "%s %s inet6 unplumb", IFCONFIG_PATH, ifname);
    argv_msg(M_INFO, &argv);
    openvpn_execve_check(&argv, es, 0, NULL);

    if (tt->type == DEV_TYPE_TUN)
    {
        const char *ifconfig_ipv6_remote = print_in6_addr(tt->remote_ipv6, 0, &gc);

        argv_printf(&argv, "%s %s inet6 plumb %s/%d %s mtu %d up",
                    IFCONFIG_PATH, ifname, ifconfig_ipv6_local,
                    tt->netbits_ipv6, ifconfig_ipv6_remote, tun_mtu);
    }
    else /* tap mode */
    {
        /* base IPv6 tap interface needs to be brought up first */
        argv_printf(&argv, "%s %s inet6 plumb up", IFCONFIG_PATH, ifname);
        argv_msg(M_INFO, &argv);

        if (!openvpn_execve_check(&argv, es, 0,
                                  "Solaris ifconfig IPv6 (prepare) failed"))
        {
            solaris_error_close(tt, es, ifname, true);
        }

        /* we might need to do "ifconfig %s inet6 auto-dhcp drop"
         * after the system has noticed the interface and fired up
         * the DHCPv6 client - but this takes quite a while, and the
         * server will ignore the DHCPv6 packets anyway.  So we don't.
         */

        /* static IPv6 addresses need to go to a subinterface (tap0:1)
         * and we cannot set an mtu here (must go to the "parent")
         */
        argv_printf(&argv, "%s %s inet6 addif %s/%d up", IFCONFIG_PATH,
                    ifname, ifconfig_ipv6_local, tt->netbits_ipv6 );
    }
    argv_msg(M_INFO, &argv);

    if (!openvpn_execve_check(&argv, es, 0, "Solaris ifconfig IPv6 failed"))
    {
        solaris_error_close(tt, es, ifname, true);
    }

    if (tt->type != DEV_TYPE_TUN)
    {
        argv_printf(&argv, "%s %s inet6 mtu %d", IFCONFIG_PATH,
                    ifname, tun_mtu);
        argv_msg(M_INFO, &argv);
        openvpn_execve_check(&argv, es, 0, "Solaris ifconfig IPv6 mtu failed");
    }
#elif defined(TARGET_OPENBSD) || defined(TARGET_NETBSD) \
    || defined(TARGET_DARWIN) || defined(TARGET_FREEBSD) \
    || defined(TARGET_DRAGONFLY)
    argv_printf(&argv, "%s %s inet6 %s/%d mtu %d up", IFCONFIG_PATH, ifname,
                ifconfig_ipv6_local, tt->netbits_ipv6, tun_mtu);
    argv_msg(M_INFO, &argv);

    openvpn_execve_check(&argv, es, S_FATAL,
                         "generic BSD ifconfig inet6 failed");

#if defined(TARGET_OPENBSD) || defined(TARGET_NETBSD) \
    || defined(TARGET_DARWIN)
    /* and, hooray, we explicitly need to add a route... */
    add_route_connected_v6_net(tt, es);
#endif
#elif defined(TARGET_AIX)
    argv_printf(&argv, "%s %s inet6 %s/%d mtu %d up", IFCONFIG_PATH, ifname,
                ifconfig_ipv6_local, tt->netbits_ipv6, tun_mtu);
    argv_msg(M_INFO, &argv);

    /* AIX ifconfig will complain if it can't find ODM path in env */
    es = env_set_create(NULL);
    env_set_add(es, "ODMDIR=/etc/objrepos");

    openvpn_execve_check(&argv, es, S_FATAL,
                         "generic BSD ifconfig inet6 failed");

    env_set_destroy(es);
#elif defined (_WIN32)
    if (tt->options.ip_win32_type == IPW32_SET_MANUAL)
    {
        msg(M_INFO, "******** NOTE:  Please manually set the v6 IP of '%s' to %s (if it is not already set)",
            ifname, ifconfig_ipv6_local);
    }
    else if (tt->options.msg_channel)
    {
        do_address_service(true, AF_INET6, tt);
        do_dns6_service(true, tt);
    }
    else
    {
        /* example: netsh interface ipv6 set address interface=42
         *                  2001:608:8003::d store=active
         */
        char iface[64];

        openvpn_snprintf(iface, sizeof(iface), "interface=%lu",
                         tt->adapter_index);
        argv_printf(&argv, "%s%sc interface ipv6 set address %s %s store=active",
                    get_win_sys_path(), NETSH_PATH_SUFFIX, iface,
                    ifconfig_ipv6_local);
        netsh_command(&argv, 4, M_FATAL);
        /* set ipv6 dns servers if any are specified */
        netsh_set_dns6_servers(tt->options.dns6, tt->options.dns6_len, ifname);
    }

    /* explicit route needed */
    if (tt->options.ip_win32_type != IPW32_SET_MANUAL)
    {
        add_route_connected_v6_net(tt, es);
    }
#else /* platforms we have no IPv6 code for */
    msg(M_FATAL, "Sorry, but I don't know how to do IPv6 'ifconfig' commands on this operating system.  You should ifconfig your TUN/TAP device manually or use an --up script.");
#endif /* outer "if defined(TARGET_xxx)" conditional */

#if !defined(TARGET_LINUX)
    gc_free(&gc);
    argv_reset(&argv);
#endif
}