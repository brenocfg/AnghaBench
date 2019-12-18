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
typedef  scalar_t__ uint16_t ;
struct openvpn_iphdr {int dummy; } ;
struct openvpn_ethhdr {int /*<<< orphan*/  proto; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int BLEN (struct buffer*) ; 
 int /*<<< orphan*/ * BPTR (struct buffer*) ; 
 int DEV_TYPE_TAP ; 
 int DEV_TYPE_TUN ; 
 scalar_t__ OPENVPN_ETH_P_IPV4 ; 
 scalar_t__ OPENVPN_ETH_P_IPV6 ; 
 int OPENVPN_IPH_GET_VER (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static int
get_tun_ip_ver(int tunnel_type, struct buffer *buf, int *ip_hdr_offset)
{
    int ip_ver = -1;

    /* for tun get ip version from ip header */
    if (tunnel_type == DEV_TYPE_TUN)
    {
        *ip_hdr_offset = 0;
        if (likely(BLEN(buf) >= (int) sizeof(struct openvpn_iphdr)))
        {
            ip_ver = OPENVPN_IPH_GET_VER(*BPTR(buf));
        }
    }
    else if (tunnel_type == DEV_TYPE_TAP)
    {
        *ip_hdr_offset = (int)(sizeof(struct openvpn_ethhdr));
        /* for tap get ip version from eth header */
        if (likely(BLEN(buf) >= *ip_hdr_offset))
        {
            const struct openvpn_ethhdr *eh = (const struct openvpn_ethhdr *) BPTR(buf);
            uint16_t proto = ntohs(eh->proto);
            if (proto == OPENVPN_ETH_P_IPV6)
            {
                ip_ver = 6;
            }
            else if (proto == OPENVPN_ETH_P_IPV4)
            {
                ip_ver = 4;
            }
        }
    }

    return ip_ver;
}