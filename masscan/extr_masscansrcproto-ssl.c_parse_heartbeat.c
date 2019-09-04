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
struct TYPE_4__ {unsigned int state; unsigned int remaining; unsigned char type; } ;
struct SSLRECORD {TYPE_2__ handshake; } ;
struct TYPE_3__ {struct SSLRECORD ssl; } ;
struct ProtocolState {int /*<<< orphan*/  base64; TYPE_1__ sub; } ;
typedef  void InteractiveData ;
struct BannerOutput {int dummy; } ;
struct Banner1 {int /*<<< orphan*/  is_capture_heartbleed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROPDOWN (unsigned int,size_t,unsigned int) ; 
 int /*<<< orphan*/  PROTO_HEARTBLEED ; 
 int /*<<< orphan*/  PROTO_VULN ; 
 int /*<<< orphan*/  UNUSEDPARM (void*) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  banout_append_base64 (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  banout_init_base64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
parse_heartbeat(
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
        LENGTH0, LENGTH1,
        CONTENTS,
        UNKNOWN,
    };

    UNUSEDPARM(more);
    UNUSEDPARM(banner1_private);

    /*
     * `for all bytes in the segment`
     *   `do a state transition for that byte `
     */
    for (i=0; i<length; i++)
    switch (state) {
            
    /* this is the 'type' field for the hearbeat. There are only two
     * values, '1' for request and '2' for response. Anything else indicates
     * that either the data was corrupted, or else it is encrypted.
     */
    case START:
        if (px[i] < 1 || 2 < px[i]) {
            state = UNKNOWN;
            break;
        }
        ssl->handshake.type = px[i];
        DROPDOWN(i,length,state);

    /* Grab the two byte length field */
    case LENGTH0:
        remaining = px[i];
        DROPDOWN(i,length,state);
    case LENGTH1:
        remaining <<= 8;
        remaining |= px[i];
        
        /* `if heartbeat response ` */
        if (ssl->handshake.type == 2) {
            
            /* if we have a non-trivial amount of data in the response, then
             * it means the "bleed" attempt succeeded. */
            if (remaining >= 16)
                banout_append(  banout, PROTO_VULN, "SSL[HEARTBLEED] ", 16);
            
            /* if we've been configured to "capture" the heartbleed contents,
             * then initialize the BASE64 encoder */
            if (banner1->is_capture_heartbleed) {
                banout_init_base64(&pstate->base64);
                banout_append(banout, PROTO_HEARTBLEED, "", 0);
            }
        }
        DROPDOWN(i,length,state);

    /* Here is where we parse the contents of the heartbeat. This is the same
     * skipping logic as the CONTENTS state within the ssl_parse_record()
     * function.*/
    case CONTENTS:
        {
            unsigned len = (unsigned)length-i;
            if (len > remaining)
                len = remaining;

            /* If this is a RESPONSE, and we've been configured to CAPTURE
             * hearbleed responses, then we write the bleeding bytes in 
             * BASE64 into the banner system. The user will be able to 
             * then do research on those bleeding bytes */
            if (ssl->handshake.type == 2 && banner1->is_capture_heartbleed) {
                banout_append_base64(banout, 
                                     PROTO_HEARTBLEED, 
                                     px+i, len,
                                     &pstate->base64);
            }

            remaining -= len;
            i += len-1;

            if (remaining == 0)
                state = UNKNOWN; /* padding */
        }

        break;
    
    /* We reach this state either because the hearbeat data is corrupted or
     * encrypted, or because we've reached the padding area after the 
     * heartbeat */
    case UNKNOWN:
    default:
        i = (unsigned)length;
    }

    /* not the handshake protocol, but we re-use their variables */
    ssl->handshake.state = state;
    ssl->handshake.remaining = remaining;
}