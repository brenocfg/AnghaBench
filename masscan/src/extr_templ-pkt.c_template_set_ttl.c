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
struct TemplateSet {unsigned int count; struct TemplatePacket* pkts; } ;
struct TemplatePacket {unsigned char* packet; unsigned int offset_ip; int /*<<< orphan*/  length; int /*<<< orphan*/  checksum_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_header_checksum (unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 

void
template_set_ttl(struct TemplateSet *tmplset, unsigned ttl)
{
    unsigned i;

    for (i=0; i<tmplset->count; i++) {
        struct TemplatePacket *tmpl = &tmplset->pkts[i];
        unsigned char *px = tmpl->packet;
        unsigned offset = tmpl->offset_ip;

        px[offset+8] = (unsigned char)(ttl);
        tmpl->checksum_ip = ip_header_checksum(    tmpl->packet,
                                                    tmpl->offset_ip,
                                                    tmpl->length);
    }
}