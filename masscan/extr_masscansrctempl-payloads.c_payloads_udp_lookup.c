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
typedef  int /*<<< orphan*/  uint64_t ;
struct PayloadsUDP {unsigned int count; TYPE_1__** list; } ;
struct TYPE_2__ {unsigned int port; unsigned char* buf; unsigned int length; unsigned int source_port; int /*<<< orphan*/  set_cookie; int /*<<< orphan*/  xsum; } ;
typedef  int /*<<< orphan*/  SET_COOKIE ;

/* Variables and functions */

int
payloads_udp_lookup(
        const struct PayloadsUDP *payloads,
        unsigned port,
        const unsigned char **px,
        unsigned *length,
        unsigned *source_port,
        uint64_t *xsum,
        SET_COOKIE *set_cookie)
{
    unsigned i;
    if (payloads == 0)
        return 0;

    port &= 0xFFFF;

    for (i=0; i<payloads->count; i++) {
        if (payloads->list[i]->port == port) {
            *px = payloads->list[i]->buf;
            *length = payloads->list[i]->length;
            *source_port = payloads->list[i]->source_port;
            *xsum = payloads->list[i]->xsum;
            *set_cookie = payloads->list[i]->set_cookie;
            return 1;
        }
    }
    return 0;
}