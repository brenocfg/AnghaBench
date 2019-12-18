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
typedef  scalar_t__ uint64_t ;
struct RangeList {int dummy; } ;
struct PayloadsUDP {unsigned int count; unsigned int max; struct PayloadUDP_Item** list; } ;
struct PayloadUDP_Item {scalar_t__ port; unsigned int source_port; unsigned int length; int /*<<< orphan*/  set_cookie; int /*<<< orphan*/  xsum; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  SET_COOKIE ;

/* Variables and functions */
 struct PayloadUDP_Item* MALLOC (int) ; 
 struct PayloadUDP_Item** REALLOCARRAY (struct PayloadUDP_Item**,size_t,int) ; 
 int /*<<< orphan*/  free (struct PayloadUDP_Item*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memmove (struct PayloadUDP_Item**,struct PayloadUDP_Item**,unsigned int) ; 
 int /*<<< orphan*/  partial_checksum (unsigned char const*,size_t) ; 
 scalar_t__ rangelist_count (struct RangeList*) ; 
 scalar_t__ rangelist_pick (struct RangeList*,scalar_t__) ; 

__attribute__((used)) static unsigned
payloads_datagram_add(struct PayloadsUDP *payloads,
            const unsigned char *buf, size_t length,
            struct RangeList *ports, unsigned source_port,
            SET_COOKIE set_cookie)
{
    unsigned count = 1;
    struct PayloadUDP_Item *p;
    uint64_t port_count = rangelist_count(ports);
    uint64_t i;

    for (i=0; i<port_count; i++) {
        /* grow the list if we need to */
        if (payloads->count + 1 > payloads->max) {
            size_t new_max = payloads->max*2 + 1;
            payloads->list = REALLOCARRAY(payloads->list, new_max, sizeof(payloads->list[0]));
            payloads->max = new_max;
        }

        /* allocate space for this record */
        p = MALLOC(sizeof(p[0]) + length);
        p->port = rangelist_pick(ports, i);
        p->source_port = source_port;
        p->length = (unsigned)length;
        memcpy(p->buf, buf, length);
        p->xsum = partial_checksum(buf, length);
        p->set_cookie = set_cookie;

        /* insert in sorted order */
        {
            unsigned j;

            for (j=0; j<payloads->count; j++) {
                if (p->port <= payloads->list[j]->port)
                    break;
            }

            if (j < payloads->count) {
                if (p->port == payloads->list[j]->port) {
                    free(payloads->list[j]);
                    count = 0; /* don't increment count */
                } else
                    memmove(payloads->list + j + 1,
                            payloads->list + j,
                            (payloads->count-j) * sizeof(payloads->list[0]));
            }
            payloads->list[j] = p;

            payloads->count += count;
        }
    }
    return count; /* zero or one */
}