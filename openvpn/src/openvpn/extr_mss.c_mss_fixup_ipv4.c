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
struct openvpn_tcphdr {int flags; } ;
struct openvpn_iphdr {scalar_t__ protocol; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  version_len; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int BLEN (struct buffer*) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int OPENVPN_IPH_GET_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ OPENVPN_IPPROTO_TCP ; 
 int OPENVPN_IP_OFFMASK ; 
 int OPENVPN_TCPH_SYN_MASK ; 
 scalar_t__ buf_advance (struct buffer*,int) ; 
 int /*<<< orphan*/  mss_fixup_dowork (struct buffer*,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_align_4 (struct buffer*) ; 

void
mss_fixup_ipv4(struct buffer *buf, int maxmss)
{
    const struct openvpn_iphdr *pip;
    int hlen;

    if (BLEN(buf) < (int) sizeof(struct openvpn_iphdr))
    {
        return;
    }

    verify_align_4(buf);
    pip = (struct openvpn_iphdr *) BPTR(buf);

    hlen = OPENVPN_IPH_GET_LEN(pip->version_len);

    if (pip->protocol == OPENVPN_IPPROTO_TCP
        && ntohs(pip->tot_len) == BLEN(buf)
        && (ntohs(pip->frag_off) & OPENVPN_IP_OFFMASK) == 0
        && hlen <= BLEN(buf)
        && BLEN(buf) - hlen
        >= (int) sizeof(struct openvpn_tcphdr))
    {
        struct buffer newbuf = *buf;
        if (buf_advance(&newbuf, hlen))
        {
            struct openvpn_tcphdr *tc = (struct openvpn_tcphdr *) BPTR(&newbuf);
            if (tc->flags & OPENVPN_TCPH_SYN_MASK)
            {
                mss_fixup_dowork(&newbuf, (uint16_t) maxmss);
            }
        }
    }
}