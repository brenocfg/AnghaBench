#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rx_enabled; int rx_overflow; int /*<<< orphan*/  ie0_value; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ CMD ; 
 scalar_t__ DCMD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DIR ; 
 scalar_t__ DSR ; 
 scalar_t__ IE0 ; 
 scalar_t__ RXDMA ; 
 int /*<<< orphan*/  RXRDYE ; 
 int /*<<< orphan*/  RXRESET ; 
 int /*<<< orphan*/  SWABORT ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_stop(SLMP_INFO *info)
{
	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):%s rx_stop()\n",
			 __FILE__,__LINE__, info->device_name );

	write_reg(info, CMD, RXRESET);

	info->ie0_value &= ~RXRDYE;
	write_reg(info, IE0, info->ie0_value);	/* disable Rx data interrupts */

	write_reg(info, RXDMA + DSR, 0);	/* disable Rx DMA */
	write_reg(info, RXDMA + DCMD, SWABORT);	/* reset/init Rx DMA */
	write_reg(info, RXDMA + DIR, 0);	/* disable Rx DMA interrupts */

	info->rx_enabled = false;
	info->rx_overflow = false;
}