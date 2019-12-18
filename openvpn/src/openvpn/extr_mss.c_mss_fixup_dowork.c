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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct openvpn_tcphdr {int /*<<< orphan*/  check; int /*<<< orphan*/  doff_res; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_CHECKSUM (int,int /*<<< orphan*/ ) ; 
 int BLEN (struct buffer*) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int /*<<< orphan*/  D_MSS ; 
 int OPENVPN_TCPH_GET_DOFF (int /*<<< orphan*/ ) ; 
 int OPENVPN_TCPOLEN_MAXSEG ; 
 scalar_t__ OPENVPN_TCPOPT_EOL ; 
 scalar_t__ OPENVPN_TCPOPT_MAXSEG ; 
 scalar_t__ OPENVPN_TCPOPT_NOP ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,int) ; 
 int htons (int) ; 
 int /*<<< orphan*/  verify_align_4 (struct buffer*) ; 

void
mss_fixup_dowork(struct buffer *buf, uint16_t maxmss)
{
    int hlen, olen, optlen;
    uint8_t *opt;
    uint16_t mssval;
    int accumulate;
    struct openvpn_tcphdr *tc;

    if (BLEN(buf) < (int) sizeof(struct openvpn_tcphdr))
    {
        return;
    }

    verify_align_4(buf);
    tc = (struct openvpn_tcphdr *) BPTR(buf);
    hlen = OPENVPN_TCPH_GET_DOFF(tc->doff_res);

    /* Invalid header length or header without options. */
    if (hlen <= (int) sizeof(struct openvpn_tcphdr)
        || hlen > BLEN(buf))
    {
        return;
    }

    for (olen = hlen - sizeof(struct openvpn_tcphdr),
         opt = (uint8_t *)(tc + 1);
         olen > 1;
         olen -= optlen, opt += optlen)
    {
        if (*opt == OPENVPN_TCPOPT_EOL)
        {
            break;
        }
        else if (*opt == OPENVPN_TCPOPT_NOP)
        {
            optlen = 1;
        }
        else
        {
            optlen = *(opt + 1);
            if (optlen <= 0 || optlen > olen)
            {
                break;
            }
            if (*opt == OPENVPN_TCPOPT_MAXSEG)
            {
                if (optlen != OPENVPN_TCPOLEN_MAXSEG)
                {
                    continue;
                }
                mssval = (opt[2]<<8)+opt[3];
                if (mssval > maxmss)
                {
                    dmsg(D_MSS, "MSS: %d -> %d", (int) mssval, (int) maxmss);
                    accumulate = htons(mssval);
                    opt[2] = (maxmss>>8)&0xff;
                    opt[3] = maxmss&0xff;
                    accumulate -= htons(maxmss);
                    ADJUST_CHECKSUM(accumulate, tc->check);
                }
            }
        }
    }
}