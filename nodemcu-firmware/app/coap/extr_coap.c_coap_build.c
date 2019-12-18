#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {int len; int /*<<< orphan*/  p; } ;
struct TYPE_9__ {size_t numopts; TYPE_3__ payload; TYPE_2__* opts; int /*<<< orphan*/  hdr; int /*<<< orphan*/  tok; } ;
typedef  TYPE_4__ coap_packet_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/  p; } ;
struct TYPE_7__ {scalar_t__ num; TYPE_1__ buf; } ;

/* Variables and functions */
 int COAP_ERR_BUFFER_TOO_SMALL ; 
 size_t coap_buildHeader (int /*<<< orphan*/ *,int*,size_t) ; 
 int coap_buildOptionHeader (scalar_t__,int,int*,size_t) ; 
 size_t coap_buildToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

int coap_build(uint8_t *buf, size_t *buflen, const coap_packet_t *pkt)
{
    size_t opts_len = 0, hdr_len = 0, tok_len = 0;
    size_t i;
    uint8_t *p = buf;
    size_t left = *buflen;
    uint16_t running_delta = 0;

    hdr_len = coap_buildHeader(&(pkt->hdr), buf, *buflen);
    p += hdr_len;
    left -= hdr_len;

    tok_len = coap_buildToken(&(pkt->tok), &(pkt->hdr), buf, *buflen);
    p += tok_len;
    left -= tok_len;

    for (i=0;i<pkt->numopts;i++)
    {
        uint8_t len, delta = 0;
        uint16_t optDelta = 0;
        int rc = 0;

        if (((size_t)(p-buf)) > *buflen)
             return COAP_ERR_BUFFER_TOO_SMALL;
        optDelta = pkt->opts[i].num - running_delta;

        rc = coap_buildOptionHeader(optDelta, pkt->opts[i].buf.len, p, left);
        p += rc;
        left -= rc;

        memcpy(p, pkt->opts[i].buf.p, pkt->opts[i].buf.len);
        p += pkt->opts[i].buf.len;
        left -= pkt->opts[i].buf.len;
        running_delta = pkt->opts[i].num;
    }

    opts_len = (p - buf) - 4;   // number of bytes used by options

    if (pkt->payload.len > 0)
    {
        if (*buflen < 4 + 1 + pkt->payload.len + opts_len)
            return COAP_ERR_BUFFER_TOO_SMALL;
        buf[4 + opts_len] = 0xFF;  // payload marker
        memcpy(buf+5 + opts_len, pkt->payload.p, pkt->payload.len);
        *buflen = opts_len + 5 + pkt->payload.len;
    }
    else
        *buflen = opts_len + 4;
    return 0;
}