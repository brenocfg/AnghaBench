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
struct cpdma_ctlr {int num_rx_desc; TYPE_1__* pool; scalar_t__ num_tx_desc; } ;
struct TYPE_2__ {scalar_t__ num_desc; } ;

/* Variables and functions */

void cpdma_set_num_rx_descs(struct cpdma_ctlr *ctlr, int num_rx_desc)
{
	ctlr->num_rx_desc = num_rx_desc;
	ctlr->num_tx_desc = ctlr->pool->num_desc - ctlr->num_rx_desc;
}