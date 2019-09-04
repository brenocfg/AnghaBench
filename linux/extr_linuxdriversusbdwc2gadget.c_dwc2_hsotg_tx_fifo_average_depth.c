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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int dwc2_hsotg_tx_fifo_count (struct dwc2_hsotg*) ; 
 int dwc2_hsotg_tx_fifo_total_depth (struct dwc2_hsotg*) ; 

int dwc2_hsotg_tx_fifo_average_depth(struct dwc2_hsotg *hsotg)
{
	int tx_fifo_count;
	int tx_fifo_depth;

	tx_fifo_depth = dwc2_hsotg_tx_fifo_total_depth(hsotg);

	tx_fifo_count = dwc2_hsotg_tx_fifo_count(hsotg);

	if (!tx_fifo_count)
		return tx_fifo_depth;
	else
		return tx_fifo_depth / tx_fifo_count;
}