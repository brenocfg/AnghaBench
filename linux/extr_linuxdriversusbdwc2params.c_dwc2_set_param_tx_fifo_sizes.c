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
struct dwc2_core_params {int* g_tx_fifo_size; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */
 int dwc2_hsotg_tx_fifo_average_depth (struct dwc2_hsotg*) ; 
 int dwc2_hsotg_tx_fifo_count (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc2_set_param_tx_fifo_sizes(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;
	int depth_average;
	int fifo_count;
	int i;

	fifo_count = dwc2_hsotg_tx_fifo_count(hsotg);

	memset(p->g_tx_fifo_size, 0, sizeof(p->g_tx_fifo_size));
	depth_average = dwc2_hsotg_tx_fifo_average_depth(hsotg);
	for (i = 1; i <= fifo_count; i++)
		p->g_tx_fifo_size[i] = depth_average;
}