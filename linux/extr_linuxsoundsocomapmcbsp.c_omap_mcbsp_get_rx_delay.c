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
typedef  scalar_t__ u16 ;
struct omap_mcbsp {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ buffer_size; } ;

/* Variables and functions */
 scalar_t__ MCBSP_READ (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBUFFSTAT ; 
 int /*<<< orphan*/  THRSH1 ; 

u16 omap_mcbsp_get_rx_delay(struct omap_mcbsp *mcbsp)
{
	u16 buffstat, threshold;

	if (mcbsp->pdata->buffer_size == 0)
		return 0;

	/* Returns the number of used locations in the buffer */
	buffstat = MCBSP_READ(mcbsp, RBUFFSTAT);
	/* RX threshold */
	threshold = MCBSP_READ(mcbsp, THRSH1);

	/* Return the number of location till we reach the threshold limit */
	if (threshold <= buffstat)
		return 0;
	else
		return threshold - buffstat;
}