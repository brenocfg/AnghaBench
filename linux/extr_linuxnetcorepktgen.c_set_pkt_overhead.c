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
typedef  int /*<<< orphan*/  u32 ;
struct pktgen_dev {int nr_labels; scalar_t__ pkt_overhead; } ;

/* Variables and functions */
 scalar_t__ SVLAN_TAG_SIZE (struct pktgen_dev*) ; 
 scalar_t__ VLAN_TAG_SIZE (struct pktgen_dev*) ; 

__attribute__((used)) static inline void set_pkt_overhead(struct pktgen_dev *pkt_dev)
{
	pkt_dev->pkt_overhead = 0;
	pkt_dev->pkt_overhead += pkt_dev->nr_labels*sizeof(u32);
	pkt_dev->pkt_overhead += VLAN_TAG_SIZE(pkt_dev);
	pkt_dev->pkt_overhead += SVLAN_TAG_SIZE(pkt_dev);
}