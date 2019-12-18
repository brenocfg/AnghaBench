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
typedef  int /*<<< orphan*/  uint16_t ;
struct openvpn_iphdr {int /*<<< orphan*/  version_len; } ;
struct openvpn_ethhdr {int /*<<< orphan*/  proto; } ;
struct openvpn_8021qhdr {int /*<<< orphan*/  proto; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int BLEN (struct buffer*) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int DEV_TYPE_TAP ; 
 int DEV_TYPE_TUN ; 
 int /*<<< orphan*/  OPENVPN_ETH_P_8021Q ; 
 scalar_t__ OPENVPN_ETH_P_IPV4 ; 
 scalar_t__ OPENVPN_ETH_P_IPV6 ; 
 int OPENVPN_IPH_GET_VER (int /*<<< orphan*/ ) ; 
 int buf_advance (struct buffer*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_align_4 (struct buffer*) ; 

__attribute__((used)) static bool
is_ipv_X(int tunnel_type, struct buffer *buf, int ip_ver)
{
    int offset;
    uint16_t proto;
    const struct openvpn_iphdr *ih;

    verify_align_4(buf);
    if (tunnel_type == DEV_TYPE_TUN)
    {
        if (BLEN(buf) < sizeof(struct openvpn_iphdr))
        {
            return false;
        }
        offset = 0;
    }
    else if (tunnel_type == DEV_TYPE_TAP)
    {
        const struct openvpn_ethhdr *eh;
        if (BLEN(buf) < (sizeof(struct openvpn_ethhdr)
                         + sizeof(struct openvpn_iphdr)))
        {
            return false;
        }
        eh = (const struct openvpn_ethhdr *)BPTR(buf);

        /* start by assuming this is a standard Eth fram */
        proto = eh->proto;
        offset = sizeof(struct openvpn_ethhdr);

        /* if this is a 802.1q frame, parse the header using the according
         * format
         */
        if (proto == htons(OPENVPN_ETH_P_8021Q))
        {
            const struct openvpn_8021qhdr *evh;
            if (BLEN(buf) < (sizeof(struct openvpn_ethhdr)
                             + sizeof(struct openvpn_iphdr)))
            {
                return false;
            }

            evh = (const struct openvpn_8021qhdr *)BPTR(buf);

            proto = evh->proto;
            offset = sizeof(struct openvpn_8021qhdr);
        }

        if (ntohs(proto) != (ip_ver == 6 ? OPENVPN_ETH_P_IPV6 : OPENVPN_ETH_P_IPV4))
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    ih = (const struct openvpn_iphdr *)(BPTR(buf) + offset);

    /* IP version is stored in the same bits for IPv4 or IPv6 header */
    if (OPENVPN_IPH_GET_VER(ih->version_len) == ip_ver)
    {
        return buf_advance(buf, offset);
    }
    else
    {
        return false;
    }
}