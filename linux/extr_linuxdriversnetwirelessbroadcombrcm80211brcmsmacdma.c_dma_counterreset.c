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
struct dma_pub {scalar_t__ txnobuf; scalar_t__ rxnobuf; scalar_t__ rxgiants; } ;

/* Variables and functions */

void dma_counterreset(struct dma_pub *pub)
{
	/* reset all software counters */
	pub->rxgiants = 0;
	pub->rxnobuf = 0;
	pub->txnobuf = 0;
}