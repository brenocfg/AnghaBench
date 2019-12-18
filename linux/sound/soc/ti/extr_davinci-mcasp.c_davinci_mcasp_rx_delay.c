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
struct davinci_mcasp {scalar_t__ fifo_base; int /*<<< orphan*/  rxnumevt; } ;

/* Variables and functions */
 scalar_t__ MCASP_RFIFOSTS_OFFSET ; 
 int /*<<< orphan*/  mcasp_get_reg (struct davinci_mcasp*,scalar_t__) ; 

__attribute__((used)) static inline u32 davinci_mcasp_rx_delay(struct davinci_mcasp *mcasp)
{
	if (!mcasp->rxnumevt)
		return 0;

	return mcasp_get_reg(mcasp, mcasp->fifo_base + MCASP_RFIFOSTS_OFFSET);
}