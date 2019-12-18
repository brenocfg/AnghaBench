#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int app_proto; } ;
struct TCP_Control_Block {int ip_them; struct TCP_Control_Block* next; scalar_t__ port_me; scalar_t__ ip_me; scalar_t__ port_them; int /*<<< orphan*/  timeout; TYPE_1__ banner1_state; scalar_t__ scripting_thread; scalar_t__ payload; scalar_t__ payload_length; scalar_t__ is_payload_dynamic; int /*<<< orphan*/  seqno_them; } ;
struct TCP_ConnectionTable {unsigned int mask; int /*<<< orphan*/  active_count; struct TCP_Control_Block* freed_list; struct TCP_Control_Block** entries; int /*<<< orphan*/  entropy; } ;
typedef  enum DestroyReason { ____Placeholder_DestroyReason } DestroyReason ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*,int,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
#define  PROTO_SMB 128 
 int /*<<< orphan*/  UNUSEDPARM (int) ; 
 TYPE_2__ banner_smb1 ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 unsigned int tcb_hash (scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpcon_flush_banners (struct TCP_ConnectionTable*,struct TCP_Control_Block*) ; 
 int /*<<< orphan*/  timeout_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcpcon_destroy_tcb(
    struct TCP_ConnectionTable *tcpcon,
    struct TCP_Control_Block *tcb,
    enum DestroyReason reason)
{
    unsigned index;
    struct TCP_Control_Block **r_entry;
    
    UNUSEDPARM(reason);

    /*
     * The TCB doesn't point to it's location in the table. Therefore, we
     * have to do a lookup to find the head pointer in the table.
     */
    index = tcb_hash(   tcb->ip_me, tcb->port_me, 
                        tcb->ip_them, tcb->port_them, 
                        tcpcon->entropy);

    /*
     * At this point, we have the head of a linked list of TCBs. Now,
     * traverse that linked list until we find our TCB
     */
    r_entry = &tcpcon->entries[index & tcpcon->mask];
    while (*r_entry && *r_entry != tcb)
        r_entry = &(*r_entry)->next;

    if (*r_entry == NULL) {
        /* TODO: this should be impossible, but it's happening anyway, about
         * 20 times on a full Internet scan. I don't know why, and I'm too
         * lazy to fix it right now, but I'll get around to eventually */
        LOG(1, "tcb: double free: %u.%u.%u.%u : %u (0x%x)\n",
                (tcb->ip_them>>24)&0xFF,
                (tcb->ip_them>>16)&0xFF,
                (tcb->ip_them>> 8)&0xFF,
                (tcb->ip_them>> 0)&0xFF,
                tcb->port_them,
                tcb->seqno_them
                );
        return;
    }

    /*
     * Print out any banners associated with this TCP session. Most of the
     * time, there'll only be one. After printing them out, delete the
     * banners.
     */
    tcpcon_flush_banners(tcpcon, tcb);
    if (tcb->is_payload_dynamic && tcb->payload_length && tcb->payload)
        free((void*)tcb->payload);
    
    if (tcb->scripting_thread)
        ; //scripting_thread_close(tcb->scripting_thread);
    tcb->scripting_thread = 0;
    
    /* KLUDGE: this needs to be made more elegant */
    switch (tcb->banner1_state.app_proto) {
        case PROTO_SMB:
            banner_smb1.cleanup(&tcb->banner1_state);
            break;
    }

    /*
     * Unlink this from the timeout system.
     */
    timeout_unlink(tcb->timeout);

    tcb->ip_them = 0;
    tcb->port_them = 0;
    tcb->ip_me = 0;
    tcb->port_me = 0;

    (*r_entry) = tcb->next;
    tcb->next = tcpcon->freed_list;
    tcpcon->freed_list = tcb;
    tcpcon->active_count--;
}