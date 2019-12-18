#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_26__ {scalar_t__ length; int /*<<< orphan*/  s; } ;
struct TYPE_25__ {scalar_t__ length; int /*<<< orphan*/  s; } ;
struct TYPE_22__ {int length; int /*<<< orphan*/ * s; } ;
struct TYPE_28__ {scalar_t__ port; TYPE_6__ query; TYPE_5__ path; TYPE_2__ host; } ;
typedef  TYPE_8__ coap_uri_t ;
struct TYPE_29__ {int len; int /*<<< orphan*/ * p; } ;
typedef  TYPE_9__ coap_rw_buffer_t ;
struct TYPE_27__ {size_t len; int /*<<< orphan*/  const* p; } ;
struct TYPE_20__ {scalar_t__ len; } ;
struct TYPE_21__ {int ver; int* id; scalar_t__ tkl; int /*<<< orphan*/  code; int /*<<< orphan*/  t; } ;
struct TYPE_19__ {size_t numopts; TYPE_7__ payload; TYPE_4__* opts; TYPE_11__ tok; TYPE_1__ hdr; } ;
typedef  TYPE_10__ coap_packet_t ;
typedef  int /*<<< orphan*/  coap_msgtype_t ;
typedef  int /*<<< orphan*/  coap_method_t ;
struct TYPE_23__ {int len; int /*<<< orphan*/ * p; } ;
struct TYPE_24__ {TYPE_3__ buf; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 scalar_t__ COAP_DEFAULT_PORT ; 
 int COAP_ERR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  COAP_OPTION_URI_HOST ; 
 int /*<<< orphan*/  COAP_OPTION_URI_PORT ; 
 int /*<<< orphan*/  NODE_DBG (char*,int) ; 
 int coap_encode_var_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int coap_split_path (TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int coap_split_query (TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int message_id ; 
 TYPE_11__ the_token ; 

int coap_make_request(coap_rw_buffer_t *scratch, coap_packet_t *pkt, coap_msgtype_t t, coap_method_t m, coap_uri_t *uri, const uint8_t *payload, size_t payload_len)
{
    int res;
    pkt->hdr.ver = 0x01;
    pkt->hdr.t = t;
    pkt->hdr.tkl = 0;
    pkt->hdr.code = m;
    pkt->hdr.id[0] = (message_id >> 8) & 0xFF;  //msgid_hi;
    pkt->hdr.id[1] = message_id & 0xFF; //msgid_lo;
    message_id++;
    NODE_DBG("message_id: %d.\n", message_id);
    pkt->numopts = 0;

    if (the_token.len) {
        pkt->hdr.tkl = the_token.len;
        pkt->tok = the_token;
    }

    if (scratch->len < 2)   // TBD...
        return COAP_ERR_BUFFER_TOO_SMALL;

    uint8_t *saved = scratch->p;

    /* split arg into Uri-* options */
    // const char *addr = uri->host.s;
    // if(uri->host.length && (strlen(addr) != uri->host.length || memcmp(addr, uri->host.s, uri->host.length) != 0)){
    if(uri->host.length){
        /* add Uri-Host */
        // addr is destination address
        pkt->opts[pkt->numopts].num = COAP_OPTION_URI_HOST;
        pkt->opts[pkt->numopts].buf.p = uri->host.s;
        pkt->opts[pkt->numopts].buf.len = uri->host.length;
        pkt->numopts++;
    }

    if (uri->port != COAP_DEFAULT_PORT) {
        pkt->opts[pkt->numopts].num = COAP_OPTION_URI_PORT;
        res = coap_encode_var_bytes(scratch->p, uri->port);
        pkt->opts[pkt->numopts].buf.len = res;
        pkt->opts[pkt->numopts].buf.p = scratch->p;
        scratch->p += res;
        scratch->len -= res;
        pkt->numopts++;
    }

    if (uri->path.length) {
        res = coap_split_path(scratch, pkt, uri->path.s, uri->path.length);
    }

    if (uri->query.length) {
        res = coap_split_query(scratch, pkt, uri->query.s, uri->query.length);
    }

    pkt->payload.p = payload;
    pkt->payload.len = payload_len;
    scratch->p = saved;     // save back the pointer.
    return 0;
}