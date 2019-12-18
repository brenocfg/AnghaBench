#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct openvpn_udphdr {int dummy; } ;
struct openvpn_iphdr {int dummy; } ;
struct gc_arena {int dummy; } ;
struct TYPE_6__ {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {scalar_t__ source; scalar_t__ dest; scalar_t__ check; } ;
struct TYPE_7__ {scalar_t__ op; } ;
struct dhcp_full {TYPE_2__ ip; TYPE_1__ udp; TYPE_3__ dhcp; } ;
struct dhcp {int dummy; } ;
struct buffer {int dummy; } ;
typedef  scalar_t__ const in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int BLEN (struct buffer*) ; 
 int /*<<< orphan*/  BOOTPC_PORT ; 
 int /*<<< orphan*/  BOOTPS_PORT ; 
 scalar_t__ BOOTREPLY ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int const DHCPACK ; 
 int const DHCPOFFER ; 
 int /*<<< orphan*/  D_ROUTE ; 
 scalar_t__ OPENVPN_IPPROTO_UDP ; 
 scalar_t__ const do_extract (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int get_dhcp_message_type (TYPE_3__*,int const) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_in_addr_t (scalar_t__ const,int /*<<< orphan*/ ,struct gc_arena*) ; 

in_addr_t
dhcp_extract_router_msg(struct buffer *ipbuf)
{
    struct dhcp_full *df = (struct dhcp_full *) BPTR(ipbuf);
    const int optlen = BLEN(ipbuf) - (sizeof(struct openvpn_iphdr) + sizeof(struct openvpn_udphdr) + sizeof(struct dhcp));

    if (optlen >= 0
        && df->ip.protocol == OPENVPN_IPPROTO_UDP
        && df->udp.source == htons(BOOTPS_PORT)
        && df->udp.dest == htons(BOOTPC_PORT)
        && df->dhcp.op == BOOTREPLY)
    {
        const int message_type = get_dhcp_message_type(&df->dhcp, optlen);
        if (message_type == DHCPACK || message_type == DHCPOFFER)
        {
            /* get the router IP address while padding out all DHCP router options */
            const in_addr_t ret = do_extract(&df->dhcp, optlen);

            /* recompute the UDP checksum */
            df->udp.check = 0;
            df->udp.check = htons(ip_checksum(AF_INET, (uint8_t *)&df->udp,
                                              sizeof(struct openvpn_udphdr) + sizeof(struct dhcp) + optlen,
                                              (uint8_t *)&df->ip.saddr, (uint8_t *)&df->ip.daddr,
                                              OPENVPN_IPPROTO_UDP));

            /* only return the extracted Router address if DHCPACK */
            if (message_type == DHCPACK)
            {
                if (ret)
                {
                    struct gc_arena gc = gc_new();
                    msg(D_ROUTE, "Extracted DHCP router address: %s", print_in_addr_t(ret, 0, &gc));
                    gc_free(&gc);
                }

                return ret;
            }
        }
    }
    return 0;
}