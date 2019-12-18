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
struct TYPE_2__ {int ip_win32_type; } ;
struct tuntap {void* local; void* remote_netmask; int topology; void* adapter_netmask; TYPE_1__ options; } ;
struct route_ipv4 {int network; int netmask; int gateway; void* flags; scalar_t__ metric; } ;
struct gc_arena {int dummy; } ;
typedef  struct env_set const env_set ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;
typedef  void* in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR (struct route_ipv4) ; 
 int /*<<< orphan*/  IFCONFIG_PATH ; 
#define  IPW32_SET_MANUAL 132 
#define  IPW32_SET_NETSH 131 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 int NI_IP_NETMASK ; 
 int NI_OPTIONS ; 
 void* RT_DEFINED ; 
 void* RT_METRIC_DEFINED ; 
 int /*<<< orphan*/  S_FATAL ; 
#define  TOP_NET30 130 
#define  TOP_P2P 129 
#define  TOP_SUBNET 128 
 int /*<<< orphan*/  add_route (struct route_ipv4*,struct tuntap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_msg (int /*<<< orphan*/ ,struct argv*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 void* create_arbitrary_remote (struct tuntap*) ; 
 int /*<<< orphan*/  env_set_add (struct env_set const*,char*) ; 
 struct env_set const* env_set_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  env_set_destroy (struct env_set const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int is_tun_p2p (struct tuntap*) ; 
 int /*<<< orphan*/  management ; 
 int /*<<< orphan*/  management_android_control (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ net_addr_ptp_v4_add (int /*<<< orphan*/ *,char const*,void**,void**) ; 
 scalar_t__ net_addr_v4_add (int /*<<< orphan*/ *,char const*,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ net_iface_mtu_set (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ net_iface_up (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  netmask_to_netbits2 (void*) ; 
 int /*<<< orphan*/  netsh_ifconfig (TYPE_1__*,char const*,int,void*,int) ; 
 int /*<<< orphan*/  openvpn_execve_check (struct argv*,struct env_set const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  openvpn_snprintf (char*,int,char*,char const*,char const*,int,char*) ; 
 char* print_in_addr_t (void*,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  solaris_error_close (struct tuntap*,struct env_set const*,char const*,int) ; 

__attribute__((used)) static void
do_ifconfig_ipv4(struct tuntap *tt, const char *ifname, int tun_mtu,
                 const struct env_set *es, openvpn_net_ctx_t *ctx)
{
    /*
     * We only handle TUN/TAP devices here, not --dev null devices.
     */
    bool tun = is_tun_p2p(tt);

#if !defined(TARGET_LINUX)
    const char *ifconfig_local = NULL;
    const char *ifconfig_remote_netmask = NULL;
    struct argv argv = argv_new();
    struct gc_arena gc = gc_new();

    /*
     * Set ifconfig parameters
     */
    ifconfig_local = print_in_addr_t(tt->local, 0, &gc);
    ifconfig_remote_netmask = print_in_addr_t(tt->remote_netmask, 0, &gc);
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

    if (tun)
    {
        if (net_addr_ptp_v4_add(ctx, ifname, &tt->local,
                                &tt->remote_netmask) < 0)
        {
            msg(M_FATAL, "Linux can't add IP to TUN interface %s", ifname);
        }
    }
    else
    {
        if (net_addr_v4_add(ctx, ifname, &tt->local,
                            netmask_to_netbits2(tt->remote_netmask)) < 0)
        {
            msg(M_FATAL, "Linux can't add IP to TAP interface %s", ifname);
        }
    }
#elif defined(TARGET_ANDROID)
    char out[64];

    char *top;
    switch (tt->topology)
    {
        case TOP_NET30:
            top = "net30";
            break;

        case TOP_P2P:
            top = "p2p";
            break;

        case TOP_SUBNET:
            top = "subnet";
            break;

        default:
            top = "undef";
    }

    openvpn_snprintf(out, sizeof(out), "%s %s %d %s", ifconfig_local,
                     ifconfig_remote_netmask, tun_mtu, top);
    management_android_control(management, "IFCONFIG", out);

#elif defined(TARGET_SOLARIS)
    /* Solaris 2.6 (and 7?) cannot set all parameters in one go...
     * example:
     *    ifconfig tun2 10.2.0.2 10.2.0.1 mtu 1450 up
     *    ifconfig tun2 netmask 255.255.255.255
     */
    if (tun)
    {
        argv_printf(&argv, "%s %s %s %s mtu %d up", IFCONFIG_PATH, ifname,
                    ifconfig_local, ifconfig_remote_netmask, tun_mtu);

        argv_msg(M_INFO, &argv);
        if (!openvpn_execve_check(&argv, es, 0, "Solaris ifconfig phase-1 failed"))
        {
            solaris_error_close(tt, es, ifname, false);
        }

        argv_printf(&argv, "%s %s netmask 255.255.255.255", IFCONFIG_PATH,
                    ifname);
    }
    else if (tt->topology == TOP_SUBNET)
    {
        argv_printf(&argv, "%s %s %s %s netmask %s mtu %d up", IFCONFIG_PATH,
                    ifname, ifconfig_local, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    else
    {
        argv_printf(&argv, "%s %s %s netmask %s up",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask);
    }

    argv_msg(M_INFO, &argv);
    if (!openvpn_execve_check(&argv, es, 0, "Solaris ifconfig phase-2 failed"))
    {
        solaris_error_close(tt, es, ifname, false);
    }

    if (!tun && tt->topology == TOP_SUBNET)
    {
        /* Add a network route for the local tun interface */
        struct route_ipv4 r;
        CLEAR(r);
        r.flags = RT_DEFINED | RT_METRIC_DEFINED;
        r.network = tt->local & tt->remote_netmask;
        r.netmask = tt->remote_netmask;
        r.gateway = tt->local;
        r.metric = 0;
        add_route(&r, tt, 0, NULL, es, NULL);
    }

#elif defined(TARGET_OPENBSD)

    in_addr_t remote_end;           /* for "virtual" subnet topology */

    /*
     * On OpenBSD, tun interfaces are persistent if created with
     * "ifconfig tunX create", and auto-destroyed if created by
     * opening "/dev/tunX" (so we just use the /dev/tunX)
     */

    /* example: ifconfig tun2 10.2.0.2 10.2.0.1 mtu 1450 netmask 255.255.255.255 up */
    if (tun)
    {
        argv_printf(&argv,
                    "%s %s %s %s mtu %d netmask 255.255.255.255 up -link0",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    else if (tt->topology == TOP_SUBNET)
    {
        remote_end = create_arbitrary_remote( tt );
        argv_printf(&argv, "%s %s %s %s mtu %d netmask %s up -link0",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    print_in_addr_t(remote_end, 0, &gc), tun_mtu,
                    ifconfig_remote_netmask);
    }
    else
    {
        argv_printf(&argv, "%s %s %s netmask %s mtu %d link0",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    argv_msg(M_INFO, &argv);
    openvpn_execve_check(&argv, es, S_FATAL, "OpenBSD ifconfig failed");

    /* Add a network route for the local tun interface */
    if (!tun && tt->topology == TOP_SUBNET)
    {
        struct route_ipv4 r;
        CLEAR(r);
        r.flags = RT_DEFINED;
        r.network = tt->local & tt->remote_netmask;
        r.netmask = tt->remote_netmask;
        r.gateway = remote_end;
        add_route(&r, tt, 0, NULL, es, NULL);
    }

#elif defined(TARGET_NETBSD)
    in_addr_t remote_end;           /* for "virtual" subnet topology */

    if (tun)
    {
        argv_printf(&argv, "%s %s %s %s mtu %d netmask 255.255.255.255 up",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    else if (tt->topology == TOP_SUBNET)
    {
        remote_end = create_arbitrary_remote(tt);
        argv_printf(&argv, "%s %s %s %s mtu %d netmask %s up", IFCONFIG_PATH,
                    ifname, ifconfig_local, print_in_addr_t(remote_end, 0, &gc),
                    tun_mtu, ifconfig_remote_netmask);
    }
    else
    {
        /*
         * NetBSD has distinct tun and tap devices
         * so we don't need the "link0" extra parameter to specify we want to do
         * tunneling at the ethernet level
         */
        argv_printf(&argv, "%s %s %s netmask %s mtu %d",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    argv_msg(M_INFO, &argv);
    openvpn_execve_check(&argv, es, S_FATAL, "NetBSD ifconfig failed");

    /* Add a network route for the local tun interface */
    if (!tun && tt->topology == TOP_SUBNET)
    {
        struct route_ipv4 r;
        CLEAR(r);
        r.flags = RT_DEFINED;
        r.network = tt->local & tt->remote_netmask;
        r.netmask = tt->remote_netmask;
        r.gateway = remote_end;
        add_route(&r, tt, 0, NULL, es, NULL);
    }

#elif defined(TARGET_DARWIN)
    /*
     * Darwin (i.e. Mac OS X) seems to exhibit similar behaviour to OpenBSD...
     */

    argv_printf(&argv, "%s %s delete", IFCONFIG_PATH, ifname);
    argv_msg(M_INFO, &argv);
    openvpn_execve_check(&argv, es, 0, NULL);
    msg(M_INFO,
        "NOTE: Tried to delete pre-existing tun/tap instance -- No Problem if failure");


    /* example: ifconfig tun2 10.2.0.2 10.2.0.1 mtu 1450 netmask 255.255.255.255 up */
    if (tun)
    {
        argv_printf(&argv, "%s %s %s %s mtu %d netmask 255.255.255.255 up",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    else
    {
        if (tt->topology == TOP_SUBNET)
        {
            argv_printf(&argv, "%s %s %s %s netmask %s mtu %d up",
                        IFCONFIG_PATH, ifname, ifconfig_local, ifconfig_local,
                        ifconfig_remote_netmask, tun_mtu);
        }
        else
        {
            argv_printf(&argv, "%s %s %s netmask %s mtu %d up", IFCONFIG_PATH,
                        ifname, ifconfig_local, ifconfig_remote_netmask,
                        tun_mtu);
        }
    }

    argv_msg(M_INFO, &argv);
    openvpn_execve_check(&argv, es, S_FATAL, "Mac OS X ifconfig failed");

    /* Add a network route for the local tun interface */
    if (!tun && tt->topology == TOP_SUBNET)
    {
        struct route_ipv4 r;
        CLEAR(r);
        r.flags = RT_DEFINED;
        r.network = tt->local & tt->remote_netmask;
        r.netmask = tt->remote_netmask;
        r.gateway = tt->local;
        add_route(&r, tt, 0, NULL, es, NULL);
    }

#elif defined(TARGET_FREEBSD) || defined(TARGET_DRAGONFLY)

    in_addr_t remote_end;           /* for "virtual" subnet topology */

    /* example: ifconfig tun2 10.2.0.2 10.2.0.1 mtu 1450 netmask 255.255.255.255 up */
    if (tun)
    {
        argv_printf(&argv, "%s %s %s %s mtu %d netmask 255.255.255.255 up",
                    IFCONFIG_PATH, ifname, ifconfig_local,
                    ifconfig_remote_netmask, tun_mtu);
    }
    else if (tt->topology == TOP_SUBNET)
    {
        remote_end = create_arbitrary_remote( tt );
        argv_printf(&argv, "%s %s %s %s mtu %d netmask %s up", IFCONFIG_PATH,
                    ifname, ifconfig_local, print_in_addr_t(remote_end, 0, &gc),
                    tun_mtu, ifconfig_remote_netmask);
    }
    else
    {
        argv_printf(&argv, "%s %s %s netmask %s mtu %d up", IFCONFIG_PATH,
                    ifname, ifconfig_local, ifconfig_remote_netmask, tun_mtu);
    }

    argv_msg(M_INFO, &argv);
    openvpn_execve_check(&argv, es, S_FATAL, "FreeBSD ifconfig failed");

    /* Add a network route for the local tun interface */
    if (!tun && tt->topology == TOP_SUBNET)
    {
        struct route_ipv4 r;
        CLEAR(r);
        r.flags = RT_DEFINED;
        r.network = tt->local & tt->remote_netmask;
        r.netmask = tt->remote_netmask;
        r.gateway = remote_end;
        add_route(&r, tt, 0, NULL, es, NULL);
    }

#elif defined(TARGET_AIX)
    {
        /* AIX ifconfig will complain if it can't find ODM path in env */
        struct env_set *aix_es = env_set_create(NULL);
        env_set_add( aix_es, "ODMDIR=/etc/objrepos" );

        if (tun)
        {
            msg(M_FATAL, "no tun support on AIX (canthappen)");
        }

        /* example: ifconfig tap0 172.30.1.1 netmask 255.255.254.0 up */
        argv_printf(&argv, "%s %s %s netmask %s mtu %d up", IFCONFIG_PATH,
                    ifname, ifconfig_local, ifconfig_remote_netmask, tun_mtu);

        argv_msg(M_INFO, &argv);
        openvpn_execve_check(&argv, aix_es, S_FATAL, "AIX ifconfig failed");

        env_set_destroy(aix_es);
    }
#elif defined (_WIN32)
    {
        ASSERT(ifname != NULL);

        switch (tt->options.ip_win32_type)
        {
            case IPW32_SET_MANUAL:
                msg(M_INFO,
                    "******** NOTE:  Please manually set the IP/netmask of '%s' to %s/%s (if it is not already set)",
                    ifname, ifconfig_local,
                    print_in_addr_t(tt->adapter_netmask, 0, &gc));
                break;

            case IPW32_SET_NETSH:
                netsh_ifconfig(&tt->options, ifname, tt->local,
                               tt->adapter_netmask, NI_IP_NETMASK|NI_OPTIONS);

                break;
        }
    }

#else  /* if defined(TARGET_LINUX) */
    msg(M_FATAL, "Sorry, but I don't know how to do 'ifconfig' commands on this operating system.  You should ifconfig your TUN/TAP device manually or use an --up script.");
#endif /* if defined(TARGET_LINUX) */

#if !defined(TARGET_LINUX)
    gc_free(&gc);
    argv_reset(&argv);
#endif
}