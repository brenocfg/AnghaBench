#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct pfring_pkthdr {scalar_t__ caplen; TYPE_1__ ts; } ;
struct TYPE_6__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct pcap_pkthdr {unsigned int caplen; TYPE_2__ ts; } ;
struct Adapter {scalar_t__ pcap; scalar_t__ ring; } ;
struct TYPE_8__ {unsigned char* (* next ) (scalar_t__,struct pcap_pkthdr*) ;} ;
struct TYPE_7__ {int (* recv ) (scalar_t__,unsigned char**,int /*<<< orphan*/ ,struct pfring_pkthdr*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* poll ) (scalar_t__,int) ;} ;

/* Variables and functions */
 TYPE_4__ PCAP ; 
 TYPE_3__ PFRING ; 
 int PF_RING_ERROR_NO_PKT_AVAILABLE ; 
 scalar_t__ is_pcap_file ; 
 int is_rx_done ; 
 int is_tx_done ; 
 int stub1 (scalar_t__,unsigned char**,int /*<<< orphan*/ ,struct pfring_pkthdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int) ; 
 unsigned char* stub3 (scalar_t__,struct pcap_pkthdr*) ; 

int rawsock_recv_packet(
    struct Adapter *adapter,
    unsigned *length,
    unsigned *secs,
    unsigned *usecs,
    const unsigned char **packet)
{
    
    if (adapter->ring) {
        /* This is for doing libpfring instead of libpcap */
        struct pfring_pkthdr hdr;
        int err;

        again:
        err = PFRING.recv(adapter->ring,
                        (unsigned char**)packet,
                        0,  /* zero-copy */
                        &hdr,
                        0   /* return immediately */
                        );
        if (err == PF_RING_ERROR_NO_PKT_AVAILABLE || hdr.caplen == 0) {
            PFRING.poll(adapter->ring, 1);
            if (is_tx_done)
                return 1;
            goto again;
        }
        if (err)
            return 1;

        *length = hdr.caplen;
        *secs = (unsigned)hdr.ts.tv_sec;
        *usecs = (unsigned)hdr.ts.tv_usec;

    } else if (adapter->pcap) {
        struct pcap_pkthdr hdr;

        *packet = PCAP.next(adapter->pcap, &hdr);

        if (*packet == NULL) {
            if (is_pcap_file) {
                //pixie_time_set_offset(10*100000);
                is_tx_done = 1;
                is_rx_done = 1;
            }
            return 1;
        }

        *length = hdr.caplen;
        *secs = (unsigned)hdr.ts.tv_sec;
        *usecs = (unsigned)hdr.ts.tv_usec;
    }


    return 0;
}