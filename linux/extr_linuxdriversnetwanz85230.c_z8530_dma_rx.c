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
typedef  int u8 ;
struct z8530_channel {scalar_t__ rxdma_on; } ;

/* Variables and functions */
 int END_FR ; 
 int /*<<< orphan*/  ERR_RES ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R6 ; 
 int /*<<< orphan*/  R7 ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 int read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_zsctrl (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z8530_rx (struct z8530_channel*) ; 
 int /*<<< orphan*/  z8530_rx_done (struct z8530_channel*) ; 

__attribute__((used)) static void z8530_dma_rx(struct z8530_channel *chan)
{
	if(chan->rxdma_on)
	{
		/* Special condition check only */
		u8 status;
	
		read_zsreg(chan, R7);
		read_zsreg(chan, R6);
		
		status=read_zsreg(chan, R1);
	
		if(status&END_FR)
		{
			z8530_rx_done(chan);	/* Fire up the next one */
		}		
		write_zsctrl(chan, ERR_RES);
		write_zsctrl(chan, RES_H_IUS);
	}
	else
	{
		/* DMA is off right now, drain the slow way */
		z8530_rx(chan);
	}	
}