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
typedef  scalar_t__ uint64_t ;
struct PacketBuffer {scalar_t__ length; int /*<<< orphan*/  px; } ;
struct Adapter {int dummy; } ;
typedef  int /*<<< orphan*/  PACKET_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pixie_usleep (int) ; 
 int /*<<< orphan*/  rawsock_send_packet (struct Adapter*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int rte_ring_sc_dequeue (int /*<<< orphan*/ *,void**) ; 
 int rte_ring_sp_enqueue (int /*<<< orphan*/ *,struct PacketBuffer*) ; 

__attribute__((used)) static void
flush_packets(struct Adapter *adapter,
    PACKET_QUEUE *packet_buffers,
    PACKET_QUEUE *transmit_queue,
    uint64_t *packets_sent,
    uint64_t *batchsize)
{
    /*
     * Send a batch of queued packets
     */
    for ( ; (*batchsize); (*batchsize)--) {
        int err;
        struct PacketBuffer *p;

        /*
         * Get the next packet from the transmit queue. This packet was
         * put there by a receive thread, and will contain things like
         * an ACK or an HTTP request
         */
        err = rte_ring_sc_dequeue(transmit_queue, (void**)&p);
        if (err) {
            break; /* queue is empty, nothing to send */
        }


        /*
         * Actually send the packet
         */
        rawsock_send_packet(adapter, p->px, (unsigned)p->length, 1);

        /*
         * Now that we are done with the packet, put it on the free list
         * of buffers that the transmit thread can reuse
         */
        for (err=1; err; ) {
            err = rte_ring_sp_enqueue(packet_buffers, p);
            if (err) {
                LOG(0, "transmit queue full (should be impossible)\n");
                pixie_usleep(10000);
            }
        }


        /*
         * Remember that we sent a packet, which will be used in
         * throttling.
         */
        (*packets_sent)++;
    }

}