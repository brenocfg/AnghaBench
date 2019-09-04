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
struct TemplateSet {struct TemplatePacket* pkts; } ;
struct TemplatePacket {unsigned char* packet; unsigned int offset_tcp; } ;

/* Variables and functions */
 size_t Proto_TCP ; 

unsigned
template_get_source_port(struct TemplateSet *tmplset)
{
    struct TemplatePacket *tmpl = &tmplset->pkts[Proto_TCP];
    const unsigned char *px = tmpl->packet;
    unsigned offset = tmpl->offset_tcp;

    return px[offset+0]<<8 | px[offset+1]<<0;
}