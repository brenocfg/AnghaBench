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
struct TYPE_5__ {int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BH_RECEIVE ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ DSR ; 
 scalar_t__ RXDMA ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char) ; 
 int read_reg (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void isr_rxdmaok(SLMP_INFO * info)
{
	/* BIT7 = EOT (end of transfer)
	 * BIT6 = EOM (end of message/frame)
	 */
	unsigned char status = read_reg(info,RXDMA + DSR) & 0xc0;

	/* clear IRQ (BIT0 must be 1 to prevent clearing DE bit) */
	write_reg(info, RXDMA + DSR, (unsigned char)(status | 1));

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_rxdmaok(), status=%02x\n",
			__FILE__,__LINE__,info->device_name,status);

	info->pending_bh |= BH_RECEIVE;
}