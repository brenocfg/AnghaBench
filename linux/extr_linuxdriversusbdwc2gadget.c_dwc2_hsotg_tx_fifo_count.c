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
struct TYPE_2__ {int num_dev_in_eps; int num_dev_perio_in_ep; scalar_t__ en_multiple_tx_fifo; } ;
struct dwc2_hsotg {TYPE_1__ hw_params; } ;

/* Variables and functions */

int dwc2_hsotg_tx_fifo_count(struct dwc2_hsotg *hsotg)
{
	if (hsotg->hw_params.en_multiple_tx_fifo)
		/* In dedicated FIFO mode we need count of IN EPs */
		return hsotg->hw_params.num_dev_in_eps;
	else
		/* In shared FIFO mode we need count of Periodic IN EPs */
		return hsotg->hw_params.num_dev_perio_in_ep;
}