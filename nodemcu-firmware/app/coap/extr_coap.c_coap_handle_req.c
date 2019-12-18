#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  coap_rw_buffer_t ;
struct TYPE_18__ {scalar_t__ code; int /*<<< orphan*/ * id; } ;
struct TYPE_19__ {int /*<<< orphan*/  tok; TYPE_3__ hdr; } ;
typedef  TYPE_4__ coap_packet_t ;
struct TYPE_16__ {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct TYPE_20__ {TYPE_1__ buf; } ;
typedef  TYPE_5__ coap_option_t ;
struct TYPE_21__ {int (* handler ) (TYPE_6__ const*,int /*<<< orphan*/ *,TYPE_4__ const*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ method; int /*<<< orphan*/ * user_entry; TYPE_2__* path; } ;
typedef  TYPE_6__ coap_endpoint_t ;
struct TYPE_17__ {int count; int /*<<< orphan*/ * elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_CONTENTTYPE_NONE ; 
 int /*<<< orphan*/  COAP_OPTION_URI_PATH ; 
 int /*<<< orphan*/  COAP_RSPCODE_NOT_FOUND ; 
 TYPE_5__* coap_findOptions (TYPE_4__ const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  coap_make_response (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* endpoints ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_6__ const*,int /*<<< orphan*/ *,TYPE_4__ const*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int coap_handle_req(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt)
{
    const coap_option_t *opt;
    int i;
    uint8_t count;
    const coap_endpoint_t *ep = endpoints;

    while(NULL != ep->handler)
    {
        if (ep->method != inpkt->hdr.code)
            goto next;
        if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_URI_PATH, &count)))
        {
            // if (count != ep->path->count)
            if ((count != ep->path->count ) && (count != ep->path->count + 1)) // +1 for /f/[function], /v/[variable]
                goto next;
            for (i=0;i<ep->path->count;i++)
            {
                if (opt[i].buf.len != strlen(ep->path->elems[i]))
                    goto next;
                if (0 != memcmp(ep->path->elems[i], opt[i].buf.p, opt[i].buf.len))
                    goto next;
            }
            // pre-path match!
            if (count==ep->path->count+1 && ep->user_entry == NULL)
                goto next;
            return ep->handler(ep, scratch, inpkt, outpkt, inpkt->hdr.id[0], inpkt->hdr.id[1]);
        }
next:
        ep++;
    }

    coap_make_response(scratch, outpkt, NULL, 0, inpkt->hdr.id[0], inpkt->hdr.id[1], &inpkt->tok, COAP_RSPCODE_NOT_FOUND, COAP_CONTENTTYPE_NONE);

    return 0;
}