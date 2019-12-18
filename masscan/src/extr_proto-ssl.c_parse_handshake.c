#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int state; unsigned int remaining; unsigned char type; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_2__ all; } ;
struct SSLRECORD {TYPE_4__ handshake; TYPE_3__ x; } ;
struct TYPE_5__ {struct SSLRECORD ssl; } ;
struct ProtocolState {TYPE_1__ sub; } ;
struct InteractiveData {int dummy; } ;
struct BannerOutput {int dummy; } ;
struct Banner1 {int /*<<< orphan*/  is_heartbleed; } ;
typedef  int /*<<< orphan*/  heartbleed_request ;

/* Variables and functions */
 int /*<<< orphan*/  DROPDOWN (unsigned int,size_t,unsigned int) ; 
 int /*<<< orphan*/  parse_server_cert (struct Banner1 const*,void*,struct ProtocolState*,unsigned char const*,unsigned int,struct BannerOutput*,struct InteractiveData*) ; 
 int /*<<< orphan*/  parse_server_hello (struct Banner1 const*,void*,struct ProtocolState*,unsigned char const*,unsigned int,struct BannerOutput*,struct InteractiveData*) ; 
 int /*<<< orphan*/  tcp_transmit (struct InteractiveData*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_handshake(
        const struct Banner1 *banner1,
        void *banner1_private,
        struct ProtocolState *pstate,
        const unsigned char *px, size_t length,
        struct BannerOutput *banout,
        struct InteractiveData *more)
{
    struct SSLRECORD *ssl = &pstate->sub.ssl;
    unsigned state = ssl->handshake.state;
    unsigned remaining = ssl->handshake.remaining;
    unsigned i;
    enum {
        START,
        LENGTH0, LENGTH1, LENGTH2,
        CONTENTS,
        UNKNOWN,
    };

    /*
     * `for all bytes in the segment`
     *   `do a state transition for that byte `
     */
    for (i=0; i<length; i++)
    switch (state) {
            
    /* There are 20 or so handshaking sub-messages, indicates by it's own
     * 'type' field, which we parse out here */
    case START:
        if (px[i] & 0x80) {
            state = UNKNOWN;
            break;
        }
        /* remember the 'type' field for use later in the CONTENT state */
        ssl->handshake.type = px[i];
        
        /* initialize the state variable that will be used by the inner
         * parsers */
        ssl->x.all.state = 0;
        DROPDOWN(i,length,state);

    /* This grabs the 'length' field. Note that unlike other length fields,
     * this one is 3 bytes long. That's because a single certificate 
     * packet can contain so many certificates in a chain that it exceeds
     * 64k kilobytes in size. */
    case LENGTH0:
        remaining = px[i];
        DROPDOWN(i,length,state);
    case LENGTH1:
        remaining <<= 8;
        remaining |= px[i];
        DROPDOWN(i,length,state);
    case LENGTH2:
        remaining <<= 8;
        remaining |= px[i];

        /* If we get a "server done" response, then it's a good time to
         * send the heartbleed request. Note that these are usually zero
         * length, so we can't process this below in the CONTENT state
         * but have to do it here at the end of the LENGTH2 state */
        if (ssl->handshake.type == 2 && banner1->is_heartbleed) {
            static const char heartbleed_request[] = 
                "\x15\x03\x02\x00\x02\x01\x80"
                "\x18\x03\x02\x00\x03\x01" "\x40\x00";
            tcp_transmit(more, heartbleed_request, sizeof(heartbleed_request)-1, 0);
        }
        DROPDOWN(i,length,state);

    /* This parses the contents of the handshake. This parser just skips
     * the data, in the same way as explained in the "ssl_parse_record()"
     * function at its CONTENT state. We may pass the fragment to an inner
     * parser, but whatever the inner parser does is independent from this
     * parser, and has no effect on this parser
     */
    case CONTENTS:
        {
            unsigned len = (unsigned)length-i;
            if (len > remaining)
                len = remaining;

            switch (ssl->handshake.type) {
                case 0: /* hello request*/
                case 1: /* client hello */
                case 3: /* DTLS hello verify request */
                case 4: /* new session ticket */
                case 12: /* server key exchange */
                case 13: /* certificate request */
                case 14: /* server done */
                case 15: /* certificate verify */
                case 16: /* client key exchange */
                case 20: /* finished */
                case 22: /* certificate status */
                default:
                    /* don't parse these types, just skip them */
                    break;
                    
                case 2: /* server hello */
                    parse_server_hello( banner1,
                                       banner1_private,
                                       pstate,
                                       px+i, len,
                                       banout,
                                       more);
                    break;
                case 11: /* server certificate */
                    parse_server_cert(  banner1,
                                      banner1_private,
                                      pstate,
                                      px+i, len,
                                      banout,
                                      more);
                    break;
            }

            remaining -= len;
            i += len-1;

            if (remaining == 0)
                state = START;
        }

        break;
    case UNKNOWN:
    default:
        i = (unsigned)length;
    }

    ssl->handshake.state = state;
    ssl->handshake.remaining = remaining;
}