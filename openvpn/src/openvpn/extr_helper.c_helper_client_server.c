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
struct options {int topology; int server_flags; int ifconfig_ipv6_pool_defined; int ifconfig_ipv6_netbits; int server_netbits_ipv6; int ifconfig_ipv6_pool_netbits; int server_bridge_defined; int server_bridge_proxy_dhcp; int ifconfig_pool_defined; int server_network; int server_netmask; int tls_server; int ifconfig_pool_start; int ifconfig_pool_end; int ifconfig_pool_netmask; int push_ifconfig_constraint_defined; int push_ifconfig_constraint_network; int push_ifconfig_constraint_netmask; int server_bridge_ip; int server_bridge_pool_start; int server_bridge_netmask; int server_bridge_pool_end; int key_method; int pull; int tls_client; scalar_t__ client; int /*<<< orphan*/  gc; void* mode; scalar_t__ shared_secret_file; void* ifconfig_remote_netmask; void* ifconfig_local; void* route_default_gateway; scalar_t__ enable_c2c; scalar_t__ server_defined; int /*<<< orphan*/  server_network_ipv6; int /*<<< orphan*/  ifconfig_ipv6_pool_base; void* ifconfig_ipv6_remote; void* ifconfig_ipv6_local; scalar_t__ server_ipv6_defined; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  dev; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int const DEV_TYPE_TAP ; 
 int const DEV_TYPE_TUN ; 
 int IFCONFIG_POOL_MIN_NETBITS ; 
 void* MODE_SERVER ; 
 int /*<<< orphan*/  M_USAGE ; 
 int SF_NOPOOL ; 
 int SF_NO_PUSH_ROUTE_GATEWAY ; 
 int const TOP_NET30 ; 
 int const TOP_P2P ; 
 int const TOP_SUBNET ; 
 int /*<<< orphan*/  add_in6_addr (int /*<<< orphan*/ ,int) ; 
 int dev_type_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  helper_add_route (int,int,struct options*) ; 
 int /*<<< orphan*/  ifconfig_pool_verify_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int netmask_to_netbits (int,int,int*) ; 
 void* print_in6_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* print_in_addr_t (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_netmask (int,struct gc_arena*) ; 
 char* print_opt_route (int,int,int /*<<< orphan*/ *) ; 
 char* print_opt_route_gateway (int,int /*<<< orphan*/ *) ; 
 char* print_opt_route_gateway_dhcp (int /*<<< orphan*/ *) ; 
 char* print_opt_topology (int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_option (struct options*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_common_subnet (char*,int,int,int) ; 

void
helper_client_server(struct options *o)
{
    struct gc_arena gc = gc_new();

#if P2MP
#if P2MP_SERVER

/*
 * Get tun/tap/null device type
 */
    const int dev = dev_type_enum(o->dev, o->dev_type);
    const int topology = o->topology;

    /*
     *
     * HELPER DIRECTIVE for IPv6
     *
     * server-ipv6 2001:db8::/64
     *
     * EXPANDS TO:
     *
     * tun-ipv6
     * push "tun-ipv6"
     * ifconfig-ipv6 2001:db8::1 2001:db8::2
     * if !nopool:
     *   ifconfig-ipv6-pool 2001:db8::1000/64
     *
     */
    if (o->server_ipv6_defined)
    {
        if (!o->server_defined)
        {
            msg(M_USAGE, "--server-ipv6 must be used together with --server");
        }
        if (o->server_flags & SF_NOPOOL)
        {
            msg( M_USAGE, "--server-ipv6 is incompatible with 'nopool' option" );
        }
        if (o->ifconfig_ipv6_pool_defined)
        {
            msg( M_USAGE, "--server-ipv6 already defines an ifconfig-ipv6-pool, so you can't also specify --ifconfig-pool explicitly");
        }

        /* local ifconfig is "base address + 1" and "+2" */
        o->ifconfig_ipv6_local =
            print_in6_addr( add_in6_addr( o->server_network_ipv6, 1), 0, &o->gc );
        o->ifconfig_ipv6_remote =
            print_in6_addr( add_in6_addr( o->server_network_ipv6, 2), 0, &o->gc );
        o->ifconfig_ipv6_netbits = o->server_netbits_ipv6;

        /* pool starts at "base address + 0x1000" - leave enough room */
        ASSERT( o->server_netbits_ipv6 <= 112 );        /* want 16 bits */

        o->ifconfig_ipv6_pool_defined = true;
        o->ifconfig_ipv6_pool_base =
            add_in6_addr( o->server_network_ipv6, 0x1000 );
        o->ifconfig_ipv6_pool_netbits = o->server_netbits_ipv6;

        push_option( o, "tun-ipv6", M_USAGE );
    }

    /*
     *
     * HELPER DIRECTIVE:
     *
     * server 10.8.0.0 255.255.255.0
     *
     * EXPANDS TO:
     *
     * mode server
     * tls-server
     * push "topology [topology]"
     *
     * if tun AND (topology == net30 OR topology == p2p):
     *   ifconfig 10.8.0.1 10.8.0.2
     *   if !nopool:
     *     ifconfig-pool 10.8.0.4 10.8.0.251
     *   route 10.8.0.0 255.255.255.0
     *   if client-to-client:
     *     push "route 10.8.0.0 255.255.255.0"
     *   else if topology == net30:
     *     push "route 10.8.0.1"
     *
     * if tap OR (tun AND topology == subnet):
     *   ifconfig 10.8.0.1 255.255.255.0
     *   if !nopool:
     *     ifconfig-pool 10.8.0.2 10.8.0.253 255.255.255.0
     *   push "route-gateway 10.8.0.1"
     *   if route-gateway unset:
     *     route-gateway 10.8.0.2
     */

    if (o->server_defined)
    {
        int netbits = -2;
        bool status = false;

        if (o->client)
        {
            msg(M_USAGE, "--server and --client cannot be used together");
        }

        if (o->server_bridge_defined || o->server_bridge_proxy_dhcp)
        {
            msg(M_USAGE, "--server and --server-bridge cannot be used together");
        }

        if (o->shared_secret_file)
        {
            msg(M_USAGE, "--server and --secret cannot be used together (you must use SSL/TLS keys)");
        }

        if (!(o->server_flags & SF_NOPOOL) && o->ifconfig_pool_defined)
        {
            msg(M_USAGE, "--server already defines an ifconfig-pool, so you can't also specify --ifconfig-pool explicitly");
        }

        if (!(dev == DEV_TYPE_TAP || dev == DEV_TYPE_TUN))
        {
            msg(M_USAGE, "--server directive only makes sense with --dev tun or --dev tap");
        }

        status = netmask_to_netbits(o->server_network, o->server_netmask, &netbits);
        if (!status)
        {
            msg(M_USAGE, "--server directive network/netmask combination is invalid");
        }

        if (netbits < 0)
        {
            msg(M_USAGE, "--server directive netmask is invalid");
        }

        if (netbits < IFCONFIG_POOL_MIN_NETBITS)
        {
            msg(M_USAGE, "--server directive netmask allows for too many host addresses (subnet must be %s or higher)",
                print_netmask(IFCONFIG_POOL_MIN_NETBITS, &gc));
        }

        if (dev == DEV_TYPE_TUN)
        {
            int pool_end_reserve = 4;

            if (netbits > 29)
            {
                msg(M_USAGE, "--server directive when used with --dev tun must define a subnet of %s or lower",
                    print_netmask(29, &gc));
            }

            if (netbits == 29)
            {
                pool_end_reserve = 0;
            }

            o->mode = MODE_SERVER;
            o->tls_server = true;

            if (topology == TOP_NET30 || topology == TOP_P2P)
            {
                o->ifconfig_local = print_in_addr_t(o->server_network + 1, 0, &o->gc);
                o->ifconfig_remote_netmask = print_in_addr_t(o->server_network + 2, 0, &o->gc);

                if (!(o->server_flags & SF_NOPOOL))
                {
                    o->ifconfig_pool_defined = true;
                    o->ifconfig_pool_start = o->server_network + 4;
                    o->ifconfig_pool_end = (o->server_network | ~o->server_netmask) - pool_end_reserve;
                    ifconfig_pool_verify_range(M_USAGE, o->ifconfig_pool_start, o->ifconfig_pool_end);
                }

                helper_add_route(o->server_network, o->server_netmask, o);
                if (o->enable_c2c)
                {
                    push_option(o, print_opt_route(o->server_network, o->server_netmask, &o->gc), M_USAGE);
                }
                else if (topology == TOP_NET30)
                {
                    push_option(o, print_opt_route(o->server_network + 1, 0, &o->gc), M_USAGE);
                }
            }
            else if (topology == TOP_SUBNET)
            {
                o->ifconfig_local = print_in_addr_t(o->server_network + 1, 0, &o->gc);
                o->ifconfig_remote_netmask = print_in_addr_t(o->server_netmask, 0, &o->gc);

                if (!(o->server_flags & SF_NOPOOL))
                {
                    o->ifconfig_pool_defined = true;
                    o->ifconfig_pool_start = o->server_network + 2;
                    o->ifconfig_pool_end = (o->server_network | ~o->server_netmask) - 2;
                    ifconfig_pool_verify_range(M_USAGE, o->ifconfig_pool_start, o->ifconfig_pool_end);
                }
                o->ifconfig_pool_netmask = o->server_netmask;

                push_option(o, print_opt_route_gateway(o->server_network + 1, &o->gc), M_USAGE);
                if (!o->route_default_gateway)
                {
                    o->route_default_gateway = print_in_addr_t(o->server_network + 2, 0, &o->gc);
                }
            }
            else
            {
                ASSERT(0);
            }

            push_option(o, print_opt_topology(topology, &o->gc), M_USAGE);
        }
        else if (dev == DEV_TYPE_TAP)
        {
            if (netbits > 30)
            {
                msg(M_USAGE, "--server directive when used with --dev tap must define a subnet of %s or lower",
                    print_netmask(30, &gc));
            }

            o->mode = MODE_SERVER;
            o->tls_server = true;
            o->ifconfig_local = print_in_addr_t(o->server_network + 1, 0, &o->gc);
            o->ifconfig_remote_netmask = print_in_addr_t(o->server_netmask, 0, &o->gc);

            if (!(o->server_flags & SF_NOPOOL))
            {
                o->ifconfig_pool_defined = true;
                o->ifconfig_pool_start = o->server_network + 2;
                o->ifconfig_pool_end = (o->server_network | ~o->server_netmask) - 1;
                ifconfig_pool_verify_range(M_USAGE, o->ifconfig_pool_start, o->ifconfig_pool_end);
            }
            o->ifconfig_pool_netmask = o->server_netmask;

            push_option(o, print_opt_route_gateway(o->server_network + 1, &o->gc), M_USAGE);
        }
        else
        {
            ASSERT(0);
        }

        /* set push-ifconfig-constraint directive */
        if ((dev == DEV_TYPE_TAP || topology == TOP_SUBNET))
        {
            o->push_ifconfig_constraint_defined = true;
            o->push_ifconfig_constraint_network = o->server_network;
            o->push_ifconfig_constraint_netmask = o->server_netmask;
        }
    }

    /*
     * HELPER DIRECTIVE:
     *
     * server-bridge 10.8.0.4 255.255.255.0 10.8.0.128 10.8.0.254
     *
     * EXPANDS TO:
     *
     * mode server
     * tls-server
     *
     * ifconfig-pool 10.8.0.128 10.8.0.254 255.255.255.0
     * push "route-gateway 10.8.0.4"
     *
     * OR
     *
     * server-bridge
     *
     * EXPANDS TO:
     *
     * mode server
     * tls-server
     *
     * if !nogw:
     *   push "route-gateway dhcp"
     */
    else if (o->server_bridge_defined | o->server_bridge_proxy_dhcp)
    {
        if (o->client)
        {
            msg(M_USAGE, "--server-bridge and --client cannot be used together");
        }

        if (!(o->server_flags & SF_NOPOOL) && o->ifconfig_pool_defined)
        {
            msg(M_USAGE, "--server-bridge already defines an ifconfig-pool, so you can't also specify --ifconfig-pool explicitly");
        }

        if (o->shared_secret_file)
        {
            msg(M_USAGE, "--server-bridge and --secret cannot be used together (you must use SSL/TLS keys)");
        }

        if (dev != DEV_TYPE_TAP)
        {
            msg(M_USAGE, "--server-bridge directive only makes sense with --dev tap");
        }

        if (o->server_bridge_defined)
        {
            verify_common_subnet("--server-bridge", o->server_bridge_ip, o->server_bridge_pool_start, o->server_bridge_netmask);
            verify_common_subnet("--server-bridge", o->server_bridge_pool_start, o->server_bridge_pool_end, o->server_bridge_netmask);
            verify_common_subnet("--server-bridge", o->server_bridge_ip, o->server_bridge_pool_end, o->server_bridge_netmask);
        }

        o->mode = MODE_SERVER;
        o->tls_server = true;

        if (o->server_bridge_defined)
        {
            o->ifconfig_pool_defined = true;
            o->ifconfig_pool_start = o->server_bridge_pool_start;
            o->ifconfig_pool_end = o->server_bridge_pool_end;
            ifconfig_pool_verify_range(M_USAGE, o->ifconfig_pool_start, o->ifconfig_pool_end);
            o->ifconfig_pool_netmask = o->server_bridge_netmask;
            push_option(o, print_opt_route_gateway(o->server_bridge_ip, &o->gc), M_USAGE);
        }
        else if (o->server_bridge_proxy_dhcp && !(o->server_flags & SF_NO_PUSH_ROUTE_GATEWAY))
        {
            push_option(o, print_opt_route_gateway_dhcp(&o->gc), M_USAGE);
        }
    }
    else
#endif /* P2MP_SERVER */

    /*
     * HELPER DIRECTIVE:
     *
     * client
     *
     * EXPANDS TO:
     *
     * pull
     * tls-client
     */
    if (o->client)
    {
        if (o->key_method != 2)
        {
            msg(M_USAGE, "--client requires --key-method 2");
        }

        o->pull = true;
        o->tls_client = true;
    }

#endif /* P2MP */

    gc_free(&gc);
}