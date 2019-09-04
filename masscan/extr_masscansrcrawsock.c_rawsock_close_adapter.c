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
struct Adapter {scalar_t__ sendq; scalar_t__ pcap; scalar_t__ ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sendqueue_destroy ) (scalar_t__) ;int /*<<< orphan*/  (* close ) (scalar_t__) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (scalar_t__) ;} ;

/* Variables and functions */
 TYPE_2__ PCAP ; 
 TYPE_1__ PFRING ; 
 int /*<<< orphan*/  free (struct Adapter*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 

__attribute__((used)) static void
rawsock_close_adapter(struct Adapter *adapter)
{
    if (adapter->ring) {
        PFRING.close(adapter->ring);
    }
    if (adapter->pcap) {
        PCAP.close(adapter->pcap);
    }
    if (adapter->sendq) {
        PCAP.sendqueue_destroy(adapter->sendq);
    }

    free(adapter);
}