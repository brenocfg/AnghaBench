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
struct cpdma_ctlr {int num_rx_desc; } ;

/* Variables and functions */

int cpdma_get_num_rx_descs(struct cpdma_ctlr *ctlr)
{
	return ctlr->num_rx_desc;
}