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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int bus_freq_mhz; } ;
struct cpdma_ctlr {TYPE_1__ params; } ;

/* Variables and functions */
 int CPDMA_MAX_RLIM_CNT ; 
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,unsigned int) ; 

u32 cpdma_chan_get_min_rate(struct cpdma_ctlr *ctlr)
{
	unsigned int divident, divisor;

	divident = ctlr->params.bus_freq_mhz * 32 * 1000;
	divisor = 1 + CPDMA_MAX_RLIM_CNT;

	return DIV_ROUND_UP(divident, divisor);
}