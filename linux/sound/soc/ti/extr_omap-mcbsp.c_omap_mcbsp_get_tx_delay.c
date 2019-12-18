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
 int /*<<< orphan*/  XBUFFSTAT ; 

__attribute__((used)) static u16 omap_mcbsp_get_tx_delay(struct omap_mcbsp *mcbsp)
{
	u16 buffstat;

	/* Returns the number of free locations in the buffer */
	buffstat = MCBSP_READ(mcbsp, XBUFFSTAT);

	/* Number of slots are different in McBSP ports */
	return mcbsp->pdata->buffer_size - buffstat;
}