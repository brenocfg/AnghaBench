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
struct TYPE_2__ {unsigned int state; unsigned char type; unsigned char flags; unsigned char len; int result; } ;
struct RDPSTUFF {TYPE_1__ cc; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 size_t AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_HEUR ; 
 int /*<<< orphan*/  PROTO_RDP ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static size_t
cc_parse(struct BannerOutput *banout, struct RDPSTUFF *rdp, const unsigned char *px, size_t length)
{
    size_t offset;
    unsigned state = rdp->cc.state;
    enum {
        TYPE, FLAGS, LENGTH, RESERVED, RESULT0, RESULT1, RESULT2, RESULT3, EXTRA, UNKNOWN_PROTOCOL
    };
    for (offset = 0; offset < length; offset++) {
        unsigned char c = px[offset];
        switch (state) {
            case TYPE:
                rdp->cc.type = c;
                state++;
                break;
            case FLAGS:
                rdp->cc.flags = c;
                state++;
                break;
            case LENGTH:
                rdp->cc.len = c;
                if (rdp->cc.len < 4) {
                    state = UNKNOWN_PROTOCOL;
                } else {
                    rdp->cc.len -= 4;
                    state++;
                }
                break;
            case RESERVED:
                switch (rdp->cc.type) {
                    case 2: /* negotiate success */
                    case 3: /* negotiate failure */
                        state = RESULT0;
                        rdp->cc.result = 0;
                        break;
                    default:
                        state = EXTRA;
                        break;
                }
                break;
            case RESULT0:
            case RESULT1:
            case RESULT2:
            case RESULT3:
                if (rdp->cc.len == 0)
                    state = EXTRA;
                else {
                    rdp->cc.len--;
                    rdp->cc.result = rdp->cc.result>>8 | (c << 24);
                    state++;
                    if (state == EXTRA) {
                        switch (rdp->cc.type) {
                            case 2:
                                if (rdp->cc.result & 2)
                                    banout_append(banout, PROTO_RDP, " NLA-supported", AUTO_LEN);
                                else
                                    banout_append(banout, PROTO_RDP, " NLA-unused", AUTO_LEN);
                                break;
                            case 3:
                                if (rdp->cc.result == 5)
                                    banout_append(banout, PROTO_RDP, " NLA-unsupported", AUTO_LEN);
                                else
                                    banout_append(banout, PROTO_RDP, " failure", AUTO_LEN);
                                break;
                            default:
                                banout_append(banout, PROTO_RDP, " unknown", AUTO_LEN);
                                break;
                        }
                    }
                }
                break;
                
            case EXTRA:
                offset = length;
                break;
            case UNKNOWN_PROTOCOL:
                banout_append(banout, PROTO_HEUR, px, length);
                offset = length;
                break;
        }
    }
    
    rdp->cc.state = state;
    return offset;
}