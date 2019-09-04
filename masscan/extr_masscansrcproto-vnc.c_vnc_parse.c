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
struct TYPE_4__ {int version; unsigned char sectype; unsigned char len; unsigned char width; unsigned char height; } ;
struct TYPE_3__ {TYPE_2__ vnc; } ;
struct ProtocolState {unsigned int state; TYPE_1__ sub; } ;
struct InteractiveData {int dummy; } ;
struct BannerOutput {int dummy; } ;
typedef  void Banner1 ;
typedef  int /*<<< orphan*/  foo ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_VNC_RFB ; 
 int /*<<< orphan*/  UNUSEDPARM (void const*) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,unsigned char const) ; 
 int /*<<< orphan*/  tcp_close (struct InteractiveData*) ; 
 int /*<<< orphan*/  tcp_transmit (struct InteractiveData*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnc_append_sectype (struct BannerOutput*,unsigned char const) ; 

__attribute__((used)) static void
vnc_parse(  const struct Banner1 *banner1,
          void *banner1_private,
          struct ProtocolState *pstate,
          const unsigned char *px, size_t length,
          struct BannerOutput *banout,
          struct InteractiveData *more)
{
    unsigned state = pstate->state;
    unsigned i;
    char foo[64];
    
    enum {
        RFB3_3_SECURITYTYPES=50,
        RFB_SECURITYERROR=60,
        RFB3_7_SECURITYTYPES=100,
        RFB_SERVERINIT=200,
        RFB_SECURITYRESULT=300,
        RFB_DONE=0x7fffffff,
    };
    
    UNUSEDPARM(banner1_private);
    UNUSEDPARM(banner1);
    
    for (i=0; i<length; i++)
        switch (state) {
            case 0: 
                
            
            case 1: case 2: case 3: case 4: case 5: case 6:
            case 7: case 8: case 9:
                state++;
                banout_append_char(banout, PROTO_VNC_RFB, px[i]);
                break;
            case 10:
                state++;
                banout_append_char(banout, PROTO_VNC_RFB, px[i]);
                break;
            case 11:
                if ('\n' == px[i]) {
                    static const char *response[] = {
                        "RFB 003.003\n",
                        "RFB 003.003\n",
                        "RFB 003.003\n",
                        "RFB 003.003\n",
                        "RFB 003.003\n",
                        "RFB 003.003\n",
                        "RFB 003.003\n",
                        "RFB 003.007\n",
                        "RFB 003.008\n",
                        "RFB 003.008\n",
                    };
                    unsigned version = pstate->sub.vnc.version % 10;
                    
                    tcp_transmit(more, response[version], 12, 0);

                    if (version < 7)
                        /* Version 3.3: the server selects either "none" or
                         * "vnc challenge/response" and informs us which one
                         * to use */
                        state = RFB3_3_SECURITYTYPES;
                    else {
                        /* Version 3.7 onwards: the server will send us a list
                         * of security types it supports, from which the
                         * client will select one */
                        state = RFB3_7_SECURITYTYPES;
                    }
                } else {
                    state = 0xFFFFFFFF;
                    tcp_close(more);
                }
                break;
            case RFB3_3_SECURITYTYPES:
            case RFB_SECURITYERROR:
            case RFB_SECURITYRESULT:
            case RFB_SERVERINIT+20:
                pstate->sub.vnc.sectype = px[i];
                state++;
                break;
            case RFB3_3_SECURITYTYPES+1:
            case RFB3_3_SECURITYTYPES+2:
            case RFB_SECURITYERROR+1:
            case RFB_SECURITYERROR+2:
            case RFB_SECURITYRESULT+1:
            case RFB_SECURITYRESULT+2:
            case RFB_SERVERINIT+21:
            case RFB_SERVERINIT+22:
                pstate->sub.vnc.sectype <<= 8;
                pstate->sub.vnc.sectype |= px[i];
                state++;
                break;
            case RFB3_3_SECURITYTYPES+3:
                pstate->sub.vnc.sectype <<= 8;
                pstate->sub.vnc.sectype |= px[i];
                banout_append(banout, PROTO_VNC_RFB, " auth=[", AUTO_LEN);
                vnc_append_sectype(banout, pstate->sub.vnc.sectype);
                banout_append(banout, PROTO_VNC_RFB, "]", AUTO_LEN);
                if (pstate->sub.vnc.sectype == 0)
                    state = RFB_SECURITYERROR;
                else if (pstate->sub.vnc.sectype == 1) {
                    /* v3.3 sectype=none
                     * We move immediately to ClientInit stage */
                    tcp_transmit(more, "\x01", 1, 0);
                    state = RFB_SERVERINIT;
                } else {
                    state = RFB_DONE;
                    tcp_close(more);
                }
                break;
            case RFB_SECURITYRESULT+3:
                pstate->sub.vnc.sectype <<= 8;
                pstate->sub.vnc.sectype |= px[i];
                if (pstate->sub.vnc.sectype == 0) {
                    /* security ok, move to client init */
                    tcp_transmit(more, "\x01", 1, 0);
                    state = RFB_SERVERINIT;
                } else {
                    /* error occurred, so grab error message */
                    state = RFB_SECURITYERROR;
                }
                break;
            case RFB_SECURITYERROR+3:
                pstate->sub.vnc.sectype <<= 8;
                pstate->sub.vnc.sectype = px[i];
                banout_append(banout, PROTO_VNC_RFB, " ERROR=", AUTO_LEN);
                state++;
                break;
            case RFB_SECURITYERROR+4:
                if (pstate->sub.vnc.sectype == 0) {
                    state = RFB_DONE;
                    tcp_close(more);
                } else {
                    pstate->sub.vnc.sectype--;
                    banout_append_char(banout, PROTO_VNC_RFB, px[i]);
                }
                break;
            case RFB3_7_SECURITYTYPES:
                pstate->sub.vnc.len = px[i];
                if (pstate->sub.vnc.len == 0)
                    state = RFB_SECURITYERROR;
                else {
                    state++;
                    banout_append(banout, PROTO_VNC_RFB, " auth=[", AUTO_LEN);
                }
                break;
            case RFB3_7_SECURITYTYPES+1:
                if (pstate->sub.vnc.len != 0) {
                    pstate->sub.vnc.len--;
                    vnc_append_sectype(banout, px[i]);
                }
                if (pstate->sub.vnc.len == 0) {
                    banout_append(banout, PROTO_VNC_RFB, "]", AUTO_LEN);
                    if (pstate->sub.vnc.version < 7) {
                        state = RFB_SERVERINIT;
                        tcp_transmit(more, "\x01", 1, 0);
                    } else if (pstate->sub.vnc.version == 7) {
                        state = RFB_SERVERINIT;
                        tcp_transmit(more, "\x01\x01", 2, 0);
                    } else {
                        state = RFB_SECURITYRESULT;
                        tcp_transmit(more, "\x01", 1, 0);
                    }
                } else {
                    banout_append(banout, PROTO_VNC_RFB, "/", AUTO_LEN);
                }
                break;
            
            
                
            case RFB_SERVERINIT:
                pstate->sub.vnc.width = px[i];
                state++;
                break;
            case RFB_SERVERINIT+1:
                pstate->sub.vnc.width <<= 8;
                pstate->sub.vnc.width |= px[i];
                sprintf_s(foo, sizeof(foo), " width=%u", pstate->sub.vnc.width);
                banout_append(banout, PROTO_VNC_RFB, foo, AUTO_LEN);
                state++;
                break;
            case RFB_SERVERINIT+2:
                pstate->sub.vnc.height = px[i];
                state++;
                break;
            case RFB_SERVERINIT+3:
                pstate->sub.vnc.height <<= 8;
                pstate->sub.vnc.height |= px[i];
                sprintf_s(foo, sizeof(foo), " height=%u", pstate->sub.vnc.height);
                banout_append(banout, PROTO_VNC_RFB, foo, AUTO_LEN);
                state++;
                break;
            
            case RFB_SERVERINIT+ 4:
            case RFB_SERVERINIT+ 5:
            case RFB_SERVERINIT+ 6:
            case RFB_SERVERINIT+ 7:
            case RFB_SERVERINIT+ 8:
            case RFB_SERVERINIT+ 9:
            case RFB_SERVERINIT+10:
            case RFB_SERVERINIT+11:
            case RFB_SERVERINIT+12:
            case RFB_SERVERINIT+13:
            case RFB_SERVERINIT+14:
            case RFB_SERVERINIT+15:
            case RFB_SERVERINIT+16:
            case RFB_SERVERINIT+17:
            case RFB_SERVERINIT+18:
            case RFB_SERVERINIT+19:
                state++;
                break;
                
            case RFB_SERVERINIT+23:
                pstate->sub.vnc.sectype <<= 8;
                pstate->sub.vnc.sectype |= px[i];
                state++;
                if (pstate->sub.vnc.sectype) {
                    banout_append(banout, PROTO_VNC_RFB, " name=[", AUTO_LEN);
                } else {
                    state = RFB_DONE;
                    tcp_close(more);
                }
                break;
                
            case RFB_SERVERINIT+24:
                pstate->sub.vnc.sectype--;
                banout_append_char(banout, PROTO_VNC_RFB, px[i]);
                if (pstate->sub.vnc.sectype == 0) {
                    banout_append(banout, PROTO_VNC_RFB, "]", AUTO_LEN);
                    state = RFB_DONE;
                    tcp_close(more);
                }
                break;


                
            case RFB_DONE:
                tcp_close(more);
                i = (unsigned)length;
                break;
            default:
                i = (unsigned)length;
                break;
        }
    pstate->state = state;
}