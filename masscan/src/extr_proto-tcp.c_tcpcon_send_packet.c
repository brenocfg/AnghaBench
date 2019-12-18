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
typedef  double uint64_t ;
struct TCP_Control_Block {unsigned char const* payload; unsigned short payload_length; int /*<<< orphan*/  seqno_them; int /*<<< orphan*/  seqno_me; int /*<<< orphan*/  port_me; int /*<<< orphan*/  ip_me; int /*<<< orphan*/  port_them; int /*<<< orphan*/  ip_them; } ;
struct TCP_ConnectionTable {int /*<<< orphan*/  transmit_queue; int /*<<< orphan*/  pkt_template; int /*<<< orphan*/  packet_buffers; } ;
struct PacketBuffer {int /*<<< orphan*/  length; int /*<<< orphan*/  px; } ;

/* Variables and functions */
 unsigned int CTRL_SMALL_WINDOW ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pixie_usleep (int) ; 
 int rte_ring_sc_dequeue (int /*<<< orphan*/ ,void**) ; 
 int rte_ring_sp_enqueue (int /*<<< orphan*/ ,struct PacketBuffer*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tcp_create_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned char const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_set_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tcpcon_send_packet(
    struct TCP_ConnectionTable *tcpcon,
    struct TCP_Control_Block *tcb,
    unsigned tcp_flags,
    const unsigned char *payload, size_t payload_length,
    unsigned ctrl)
{
    struct PacketBuffer *response = 0;
    int err = 0;
    uint64_t wait = 100;


    /* Get a buffer for sending the response packet. This thread doesn't
     * send the packet itself. Instead, it formats a packet, then hands
     * that packet off to a transmit thread for later transmission. */
    for (err=1; err; ) {
        err = rte_ring_sc_dequeue(tcpcon->packet_buffers, (void**)&response);
        if (err != 0) {
            static int is_warning_printed = 0;
            if (!is_warning_printed) {
                LOG(0, "packet buffers empty (should be impossible)\n");
                is_warning_printed = 1;
            }
            fflush(stdout);
            pixie_usleep(wait = (uint64_t)(wait *1.5)); /* no packet available */
        }
        //if (wait != 100)
        //    ; //printf("\n");FIXME
    }
    if (response == NULL)
        return;

    /* Format the packet as requested. Note that there are really only
     * four types of packets:
     * 1. a SYN-ACK packet with no payload
     * 2. an ACK packet with no payload
     * 3. a RST packet with no pacyload
     * 4. a PSH-ACK packet WITH PAYLOAD
     */
    response->length = tcp_create_packet(
        tcpcon->pkt_template,
        tcb->ip_them, tcb->port_them,
        tcb->ip_me, tcb->port_me,
        tcb->seqno_me, tcb->seqno_them,
        tcp_flags,
        payload, payload_length,
        response->px, sizeof(response->px)
        );

    /*
     * KLUDGE:
     */
    if (ctrl & CTRL_SMALL_WINDOW) {
        tcp_set_window(response->px, response->length, 600);
    }
    //tcp_set_window(response->px, response->length, 600);

    /* If we have payload, then:
     * 1. remember the payload so we can resend it
     */
    tcb->payload = payload;
    tcb->payload_length = (unsigned short)payload_length;

    /* Put this buffer on the transmit queue. Remember: transmits happen
     * from a transmit-thread only, and this function is being called
     * from a receive-thread. Therefore, instead of transmiting ourselves,
     * we hae to queue it up for later transmission. */
    for (err=1; err; ) {
        err = rte_ring_sp_enqueue(tcpcon->transmit_queue, response);
        if (err != 0) {
            LOG(0, "transmit queue full (should be impossible)\n");
            pixie_usleep(100); /* no space available */
        }
    }
}