#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int state; unsigned char len; unsigned char type; int dstref; unsigned char flags; int /*<<< orphan*/  srcref; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct RDPSTUFF {TYPE_2__ cotp; TYPE_1__ cc; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 size_t AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_HEUR ; 
 int /*<<< orphan*/  PROTO_RDP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,...) ; 
 size_t cc_parse (struct BannerOutput*,struct RDPSTUFF*,unsigned char const*,size_t) ; 

__attribute__((used)) static size_t
cotp_parse(struct BannerOutput *banout, struct RDPSTUFF *rdp, const unsigned char *px, size_t length)
{
    size_t offset;
    unsigned state = rdp->cotp.state;
    enum {
        LENGTH, PDU_TYPE, DSTREF0, DSTREF1, SRCREF0, SRCREF1,
        FLAGS, CONTENT, UNKNOWN_PROTOCOL,
    };
    for (offset = 0; offset < length; offset++) {
        unsigned char c = px[offset];
        switch (state) {
            case LENGTH:
                rdp->cotp.len = c;
                if (rdp->cotp.len < 6) {
                    state = UNKNOWN_PROTOCOL;
                } else {
                    rdp->cotp.len -= 6;
                    state++;
                }
                break;
            case PDU_TYPE:
                rdp->cotp.type = c;
                rdp->cotp.srcref = 0;
                rdp->cotp.dstref = 0;
                state++;
                break;
            case DSTREF0:
            case DSTREF1:
                rdp->cotp.dstref = rdp->cotp.dstref<<8 | c;
                state++;
                break;
            case SRCREF0:
            case SRCREF1:
                rdp->cotp.dstref = rdp->cotp.dstref<<8 | c;
                state++;
                break;
            case FLAGS:
                rdp->cotp.flags = c;
                rdp->cc.state = 0;
                state++;
                break;
            case CONTENT:
                switch (rdp->cotp.type) {
                    case 0xd0: /* connect confirm */
                    {
                        size_t length2 = rdp->cotp.len;
                        size_t bytes_parsed;
                        
                        /* In case the TPKT length is more bytes than are in this packet */
                        if (length2 >= length - offset)
                            length2 = length - offset;
                        
                        bytes_parsed = cc_parse(banout, rdp, px + offset, length2);
                        
                        /* Track how many bytes the sub-parsers parsed, remembering
                         * that when the for-loop increments, it'll increment the offset
                         * by 1. */
                        assert(bytes_parsed != 0);
                        offset += bytes_parsed - 1;
                        rdp->cotp.len -= (unsigned char)bytes_parsed;
                        
                        /* If we have bytes left in the TPKT, then stay in this state,
                         * otherwise transition to the next TPKT */
                        if (rdp->cotp.len)
                            state = CONTENT;
                        else
                            state = UNKNOWN_PROTOCOL;

                    }
                        break;
                    default:
                        banout_append(banout, PROTO_RDP, " COTPPDU=unknown", AUTO_LEN);
                        offset = length;
                        break;
                }
                break;
            case UNKNOWN_PROTOCOL:
                banout_append(banout, PROTO_HEUR, px, length);
                offset = length;
                break;
        }
    }
    
    rdp->cotp.state = state;
    return offset;
}