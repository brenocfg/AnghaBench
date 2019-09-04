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
struct TemplateSet {int dummy; } ;
struct Adapter {int dummy; } ;
typedef  int /*<<< orphan*/  px ;

/* Variables and functions */
 int /*<<< orphan*/  rawsock_send_packet (struct Adapter*,unsigned char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  template_set_target (struct TemplateSet*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned char*,int,size_t*) ; 

void
rawsock_send_probe(
    struct Adapter *adapter,
    unsigned ip_them, unsigned port_them,
    unsigned ip_me, unsigned port_me,
    unsigned seqno, unsigned flush,
    struct TemplateSet *tmplset)
{
    unsigned char px[2048];
    size_t packet_length;

    /*
     * Construct the destination packet
     */
    template_set_target(tmplset, ip_them, port_them, ip_me, port_me, seqno,
        px, sizeof(px), &packet_length);
    
    /*
     * Send it
     */
    rawsock_send_packet(adapter, px, (unsigned)packet_length, flush);
}