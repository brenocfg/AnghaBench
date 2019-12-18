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
typedef  int /*<<< orphan*/  uint64_t ;
struct TemplatePacket {unsigned char* packet; int offset_app; int length; int /*<<< orphan*/  payloads; } ;
typedef  scalar_t__ (* SET_COOKIE ) (unsigned char*,unsigned int,unsigned int) ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  payloads_udp_lookup (int /*<<< orphan*/ ,unsigned int,unsigned char const**,unsigned int*,unsigned int*,int /*<<< orphan*/ *,scalar_t__ (*) (unsigned char*,unsigned int,unsigned int)) ; 

__attribute__((used)) static void
udp_payload_fixup(struct TemplatePacket *tmpl, unsigned port, unsigned seqno)
{
    const unsigned char *px2 = 0;
    unsigned length2 = 0;
    unsigned source_port2 = 0x1000;
    uint64_t xsum2 = 0;
    unsigned char *px = tmpl->packet;
    SET_COOKIE set_cookie = 0;

    UNUSEDPARM(seqno);

    payloads_udp_lookup(tmpl->payloads,
                    port,
                    &px2,
                    &length2,
                    &source_port2,
                    &xsum2,
                    &set_cookie);

    memcpy( px+tmpl->offset_app,
            px2,
            length2);

    if (set_cookie)
        xsum2 += set_cookie(px+tmpl->offset_app,
                    length2,
                    seqno);

    tmpl->length = tmpl->offset_app + length2;
}