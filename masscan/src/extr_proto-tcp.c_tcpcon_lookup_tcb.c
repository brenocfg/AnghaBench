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
struct TCP_Control_Block {unsigned int ip_me; unsigned int ip_them; unsigned short port_me; unsigned short port_them; struct TCP_Control_Block* next; } ;
struct TCP_ConnectionTable {unsigned int mask; struct TCP_Control_Block** entries; int /*<<< orphan*/  entropy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EQUALS (struct TCP_Control_Block*,struct TCP_Control_Block*) ; 
 unsigned int tcb_hash (unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

struct TCP_Control_Block *
tcpcon_lookup_tcb(
    struct TCP_ConnectionTable *tcpcon,
    unsigned ip_me, unsigned ip_them,
    unsigned port_me, unsigned port_them)
{
    unsigned index;
    struct TCP_Control_Block tmp;
    struct TCP_Control_Block *tcb;

    tmp.ip_me = ip_me;
    tmp.ip_them = ip_them;
    tmp.port_me = (unsigned short)port_me;
    tmp.port_them = (unsigned short)port_them;

    index = tcb_hash(ip_me, port_me, ip_them, port_them, tcpcon->entropy);

    tcb = tcpcon->entries[index & tcpcon->mask];
    while (tcb && !EQUALS(tcb, &tmp)) {
        tcb = tcb->next;
    }

    return tcb;
}