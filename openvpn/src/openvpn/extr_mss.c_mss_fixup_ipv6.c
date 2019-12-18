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
struct openvpn_tcphdr {int flags; } ;
struct openvpn_ipv6hdr {scalar_t__ nexthdr; int /*<<< orphan*/  payload_len; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int BLEN (struct buffer*) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 scalar_t__ OPENVPN_IPPROTO_TCP ; 
 int OPENVPN_TCPH_SYN_MASK ; 
 scalar_t__ buf_advance (struct buffer*,int) ; 
 int /*<<< orphan*/  mss_fixup_dowork (struct buffer*,scalar_t__) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_align_4 (struct buffer*) ; 

void
mss_fixup_ipv6(struct buffer *buf, int maxmss)
{
    const struct openvpn_ipv6hdr *pip6;
    struct buffer newbuf;

    if (BLEN(buf) < (int) sizeof(struct openvpn_ipv6hdr))
    {
        return;
    }

    verify_align_4(buf);
    pip6 = (struct openvpn_ipv6hdr *) BPTR(buf);

    /* do we have the full IPv6 packet?
     * "payload_len" does not include IPv6 header (+40 bytes)
     */
    if (BLEN(buf) != (int) ntohs(pip6->payload_len)+40)
    {
        return;
    }

    /* follow header chain until we reach final header, then check for TCP
     *
     * An IPv6 packet could, theoretically, have a chain of multiple headers
     * before the final header (TCP, UDP, ...), so we'd need to walk that
     * chain (see RFC 2460 and RFC 6564 for details).
     *
     * In practice, "most typically used" extension headers (AH, routing,
     * fragment, mobility) are very unlikely to be seen inside an OpenVPN
     * tun, so for now, we only handle the case of "single next header = TCP"
     */
    if (pip6->nexthdr != OPENVPN_IPPROTO_TCP)
    {
        return;
    }

    /* skip IPv6 header (40 bytes),
     * verify remainder is large enough to contain a full TCP header
     */
    newbuf = *buf;
    if (buf_advance( &newbuf, 40 )
        && BLEN(&newbuf) >= (int) sizeof(struct openvpn_tcphdr))
    {
        struct openvpn_tcphdr *tc = (struct openvpn_tcphdr *) BPTR(&newbuf);
        if (tc->flags & OPENVPN_TCPH_SYN_MASK)
        {
            mss_fixup_dowork(&newbuf, (uint16_t) maxmss-20);
        }
    }
}