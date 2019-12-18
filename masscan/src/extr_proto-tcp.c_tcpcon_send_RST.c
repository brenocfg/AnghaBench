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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  tcb ;
struct TCP_Control_Block {unsigned int ip_me; unsigned int ip_them; unsigned short port_me; unsigned short port_them; void* ackno_them; void* seqno_them; void* ackno_me; void* seqno_me; } ;
struct TCP_ConnectionTable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGSEND (struct TCP_Control_Block*,char*) ; 
 int /*<<< orphan*/  memset (struct TCP_Control_Block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcpcon_send_packet (struct TCP_ConnectionTable*,struct TCP_Control_Block*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcpcon_send_RST(
                struct TCP_ConnectionTable *tcpcon,
                unsigned ip_me, unsigned ip_them,
                unsigned port_me, unsigned port_them,
                uint32_t seqno_them, uint32_t ackno_them)
{
    struct TCP_Control_Block tcb;
    
    memset(&tcb, 0, sizeof(tcb));
    
    tcb.ip_me = ip_me;
    tcb.ip_them = ip_them;
    tcb.port_me = (unsigned short)port_me;
    tcb.port_them = (unsigned short)port_them;
    tcb.seqno_me = ackno_them;
    tcb.ackno_me = seqno_them + 1;
    tcb.seqno_them = seqno_them + 1;
    tcb.ackno_them = ackno_them;
    
    LOGSEND(&tcb, "peer(RST) fake");
    tcpcon_send_packet(tcpcon, &tcb, 0x04, 0, 0, 0);
}