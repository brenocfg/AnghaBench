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
struct TYPE_4__ {int port_num; int irq_occurred; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_ISR ; 
 unsigned char IER2 ; 
 unsigned char TIMER0 ; 
 unsigned char TIMER2 ; 
 scalar_t__ TMCS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isr_timer(SLMP_INFO * info)
{
	unsigned char timer = (info->port_num & 1) ? TIMER2 : TIMER0;

	/* IER2<7..4> = timer<3..0> interrupt enables (0=disabled) */
	write_reg(info, IER2, 0);

	/* TMCS, Timer Control/Status Register
	 *
	 * 07      CMF, Compare match flag (read only) 1=match
	 * 06      ECMI, CMF Interrupt Enable: 0=disabled
	 * 05      Reserved, must be 0
	 * 04      TME, Timer Enable
	 * 03..00  Reserved, must be 0
	 *
	 * 0000 0000
	 */
	write_reg(info, (unsigned char)(timer + TMCS), 0);

	info->irq_occurred = true;

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_timer()\n",
			__FILE__,__LINE__,info->device_name);
}