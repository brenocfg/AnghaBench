#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Adapter {scalar_t__ sendq; int /*<<< orphan*/  pcap; } ;
struct TYPE_2__ {scalar_t__ (* sendqueue_alloc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sendqueue_destroy ) (scalar_t__) ;int /*<<< orphan*/  (* sendqueue_transmit ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ PCAP ; 
 int /*<<< orphan*/  SENDQ_SIZE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 

void
rawsock_flush(struct Adapter *adapter)
{
    if (adapter->sendq) {
        PCAP.sendqueue_transmit(adapter->pcap, adapter->sendq, 0);

        /* Dude, I totally forget why this step is necessary. I vaguely
         * remember there's a good reason for it though */
        PCAP.sendqueue_destroy(adapter->sendq);
        adapter->sendq =  PCAP.sendqueue_alloc(SENDQ_SIZE);
    }

}