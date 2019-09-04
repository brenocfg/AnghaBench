#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char ie1_value; int serial_signals; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 unsigned char CCTS ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 unsigned char IDLE ; 
 int MISCSTATUS_CTS_LATCHED ; 
 int /*<<< orphan*/  SR1 ; 
 int SerialSignal_CTS ; 
 unsigned char UDRN ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  get_signals (TYPE_1__*) ; 
 int /*<<< orphan*/  isr_io_pin (TYPE_1__*,int) ; 
 int /*<<< orphan*/  isr_txeom (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char read_reg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void isr_txint(SLMP_INFO * info)
{
	unsigned char status = read_reg(info, SR1) & info->ie1_value & (UDRN + IDLE + CCTS);

	/* clear status bits */
	write_reg(info, SR1, status);

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_txint status=%02x\n",
			__FILE__,__LINE__,info->device_name,status);

	if (status & (UDRN + IDLE))
		isr_txeom(info, status);

	if (status & CCTS) {
		/* simulate a common modem status change interrupt
		 * for our handler
		 */
		get_signals( info );
		isr_io_pin(info,
			MISCSTATUS_CTS_LATCHED|(info->serial_signals&SerialSignal_CTS));

	}
}