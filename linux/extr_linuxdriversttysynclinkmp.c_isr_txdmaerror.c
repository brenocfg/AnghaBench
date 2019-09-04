#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DSR ; 
 scalar_t__ TXDMA ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char) ; 
 int read_reg (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void isr_txdmaerror(SLMP_INFO * info)
{
	/* BIT5 = BOF (buffer overflow)
	 * BIT4 = COF (counter overflow)
	 */
	unsigned char status = read_reg(info,TXDMA + DSR) & 0x30;

	/* clear IRQ (BIT0 must be 1 to prevent clearing DE bit) */
	write_reg(info, TXDMA + DSR, (unsigned char)(status | 1));

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_txdmaerror(), status=%02x\n",
			__FILE__,__LINE__,info->device_name,status);
}