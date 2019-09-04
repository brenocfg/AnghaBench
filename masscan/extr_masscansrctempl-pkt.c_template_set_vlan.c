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
struct TemplatePacket {int length; unsigned char* packet; int offset_ip; int offset_tcp; int offset_app; } ;

/* Variables and functions */
 unsigned char* MALLOC (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

void
template_set_vlan(struct TemplateSet *tmplset, unsigned vlan)
{
    unsigned i;
    
    for (i=0; i<tmplset->count; i++) {
        struct TemplatePacket *tmpl = &tmplset->pkts[i];
        unsigned char *px;

        if (tmpl->length < 14)
            continue;
        
        px = MALLOC(tmpl->length + 4);
        memcpy(px, tmpl->packet, 12);
        memcpy(px+16, tmpl->packet+12, tmpl->length - 12);
        
        px[12] = 0x81;
        px[13] = 0x00;
        px[14] = (unsigned char)(vlan>>8);
        px[15] = (unsigned char)(vlan>>0);
        
        tmpl->packet = px;
        tmpl->length += 4;
        
        tmpl->offset_ip += 4;
        tmpl->offset_tcp += 4;
        tmpl->offset_app += 4;
    }
}