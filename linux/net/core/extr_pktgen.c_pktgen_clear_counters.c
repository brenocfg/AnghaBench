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
struct pktgen_dev {int seq_num; scalar_t__ errors; scalar_t__ tx_bytes; scalar_t__ sofar; scalar_t__ idle_acc; } ;

/* Variables and functions */

__attribute__((used)) static void pktgen_clear_counters(struct pktgen_dev *pkt_dev)
{
	pkt_dev->seq_num = 1;
	pkt_dev->idle_acc = 0;
	pkt_dev->sofar = 0;
	pkt_dev->tx_bytes = 0;
	pkt_dev->errors = 0;
}