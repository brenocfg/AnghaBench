#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct TYPE_15__ {int* p; int len; } ;
typedef  TYPE_5__ coap_rw_buffer_t ;
typedef  int /*<<< orphan*/  coap_responsecode_t ;
struct TYPE_14__ {void* const* p; size_t len; } ;
struct TYPE_17__ {scalar_t__ len; } ;
struct TYPE_11__ {int ver; scalar_t__ tkl; void** id; int /*<<< orphan*/  code; int /*<<< orphan*/  t; } ;
struct TYPE_16__ {int numopts; TYPE_4__ payload; TYPE_3__* opts; TYPE_7__ tok; TYPE_1__ hdr; } ;
typedef  TYPE_6__ coap_packet_t ;
typedef  scalar_t__ coap_content_type_t ;
typedef  TYPE_7__ coap_buffer_t ;
struct TYPE_12__ {int* p; int len; } ;
struct TYPE_13__ {TYPE_2__ buf; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int COAP_ERR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  COAP_OPTION_CONTENT_FORMAT ; 
 int /*<<< orphan*/  COAP_TYPE_ACK ; 

int coap_make_response(coap_rw_buffer_t *scratch, coap_packet_t *pkt, const uint8_t *content, size_t content_len, uint8_t msgid_hi, uint8_t msgid_lo, const coap_buffer_t* tok, coap_responsecode_t rspcode, coap_content_type_t content_type)
{
    pkt->hdr.ver = 0x01;
    pkt->hdr.t = COAP_TYPE_ACK;
    pkt->hdr.tkl = 0;
    pkt->hdr.code = rspcode;
    pkt->hdr.id[0] = msgid_hi;
    pkt->hdr.id[1] = msgid_lo;
    pkt->numopts = 1;

    // need token in response
    if (tok) {
        pkt->hdr.tkl = tok->len;
        pkt->tok = *tok;
    }

    // safe because 1 < MAXOPT
    pkt->opts[0].num = COAP_OPTION_CONTENT_FORMAT;
    pkt->opts[0].buf.p = scratch->p;
    if (scratch->len < 2)
        return COAP_ERR_BUFFER_TOO_SMALL;
    scratch->p[0] = ((uint16_t)content_type & 0xFF00) >> 8;
    scratch->p[1] = ((uint16_t)content_type & 0x00FF);
    pkt->opts[0].buf.len = 2;
    pkt->payload.p = content;
    pkt->payload.len = content_len;
    return 0;
}