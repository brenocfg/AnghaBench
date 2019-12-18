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
struct TYPE_2__ {int MCI_SR; int MCI_IMR; } ;

/* Variables and functions */
 TYPE_1__* AT91C_BASE_MCI ; 
 int /*<<< orphan*/  AT91F_MCI_Device_Handler (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MCI_Device ; 

void AT91F_MCI_Handler(void)
{
	int status;

	status = ( AT91C_BASE_MCI->MCI_SR & AT91C_BASE_MCI->MCI_IMR );

	AT91F_MCI_Device_Handler(&MCI_Device,status);
}