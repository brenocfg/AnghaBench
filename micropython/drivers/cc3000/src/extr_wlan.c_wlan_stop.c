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
struct TYPE_2__ {scalar_t__ (* ReadWlanInterruptPin ) () ;scalar_t__ pucTxCommandBuffer; int /*<<< orphan*/  (* WriteWlanPin ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SpiClose () ; 
 int /*<<< orphan*/  WLAN_DISABLE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 () ; 
 TYPE_1__ tSLInformation ; 

void wlan_stop(void)
{
	// Chip disable
	tSLInformation.WriteWlanPin( WLAN_DISABLE );

	// Wait till IRQ line goes high...
	while(tSLInformation.ReadWlanInterruptPin() == 0)
	{
	}

	// Free the used by WLAN Driver memory
	if (tSLInformation.pucTxCommandBuffer)
	{
		tSLInformation.pucTxCommandBuffer = 0;
	}

	SpiClose();
}