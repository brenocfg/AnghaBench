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
struct TYPE_2__ {int MCI_SR; } ;

/* Variables and functions */
 TYPE_1__* AT91C_BASE_MCI ; 
 int volatile AT91C_MCI_NOTBUSY ; 

void AT91F_MCIDeviceWaitReady(unsigned int timeout)
{
	volatile int status;
	
	do
	{
		status = AT91C_BASE_MCI->MCI_SR;
		timeout--;
	}
	while( !(status & AT91C_MCI_NOTBUSY)  && (timeout>0) );	
}