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
typedef  int u32 ;
struct mu3h_sch_ep_info {int esit; int offset; int num_budget_microframes; } ;
struct mu3h_sch_bw_info {int* bus_bw; } ;

/* Variables and functions */
 int XHCI_MTK_MAX_ESIT ; 

__attribute__((used)) static void update_bus_bw(struct mu3h_sch_bw_info *sch_bw,
	struct mu3h_sch_ep_info *sch_ep, int bw_cost)
{
	u32 num_esit;
	u32 base;
	int i;
	int j;

	num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	for (i = 0; i < num_esit; i++) {
		base = sch_ep->offset + i * sch_ep->esit;
		for (j = 0; j < sch_ep->num_budget_microframes; j++)
			sch_bw->bus_bw[base + j] += bw_cost;
	}
}