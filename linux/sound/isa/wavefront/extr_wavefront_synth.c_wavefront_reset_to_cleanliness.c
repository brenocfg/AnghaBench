#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  irq_ok; int /*<<< orphan*/  data_port; int /*<<< orphan*/  control_port; int /*<<< orphan*/  irq; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  STAT_CAN_READ ; 
 int WFC_HARDWARE_VERSION ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int ramcheck_time ; 
 int reset_time ; 
 int /*<<< orphan*/  snd_printk (char*,...) ; 
 int snd_wavefront_interrupt_bits (int /*<<< orphan*/ ) ; 
 int wavefront_read (TYPE_1__*) ; 
 int /*<<< orphan*/  wavefront_should_cause_interrupt (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wavefront_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wavefront_reset_to_cleanliness (snd_wavefront_t *dev)

{
	int bits;
	int hwv[2];

	/* IRQ already checked */

	bits = snd_wavefront_interrupt_bits (dev->irq);

	/* try reset of port */

	outb (0x0, dev->control_port); 
  
	/* At this point, the board is in reset, and the H/W initialization
	   register is accessed at the same address as the data port.
     
	   Bit 7 - Enable IRQ Driver	
	   0 - Tri-state the Wave-Board drivers for the PC Bus IRQs
	   1 - Enable IRQ selected by bits 5:3 to be driven onto the PC Bus.
     
	   Bit 6 - MIDI Interface Select

	   0 - Use the MIDI Input from the 26-pin WaveBlaster
	   compatible header as the serial MIDI source
	   1 - Use the MIDI Input from the 9-pin D connector as the
	   serial MIDI source.
     
	   Bits 5:3 - IRQ Selection
	   0 0 0 - IRQ 2/9
	   0 0 1 - IRQ 5
	   0 1 0 - IRQ 12
	   0 1 1 - IRQ 15
	   1 0 0 - Reserved
	   1 0 1 - Reserved
	   1 1 0 - Reserved
	   1 1 1 - Reserved
     
	   Bits 2:1 - Reserved
	   Bit 0 - Disable Boot ROM
	   0 - memory accesses to 03FC30-03FFFFH utilize the internal Boot ROM
	   1 - memory accesses to 03FC30-03FFFFH are directed to external 
	   storage.
     
	*/

	/* configure hardware: IRQ, enable interrupts, 
	   plus external 9-pin MIDI interface selected
	*/

	outb (0x80 | 0x40 | bits, dev->data_port);	
  
	/* CONTROL REGISTER

	   0 Host Rx Interrupt Enable (1=Enabled)      0x1
	   1 Unused                                    0x2
	   2 Unused                                    0x4
	   3 Unused                                    0x8
	   4 Host Tx Interrupt Enable                 0x10
	   5 Mute (0=Mute; 1=Play)                    0x20
	   6 Master Interrupt Enable (1=Enabled)      0x40
	   7 Master Reset (0=Reset; 1=Run)            0x80

	   Take us out of reset, mute output, master + TX + RX interrupts on.
	   
	   We'll get an interrupt presumably to tell us that the TX
	   register is clear.
	*/

	wavefront_should_cause_interrupt(dev, 0x80|0x40|0x10|0x1,
					 dev->control_port,
					 (reset_time*HZ)/100);

	/* Note: data port is now the data port, not the h/w initialization
	   port.
	 */

	if (!dev->irq_ok) {
		snd_printk ("intr not received after h/w un-reset.\n");
		goto gone_bad;
	} 

	/* Note: data port is now the data port, not the h/w initialization
	   port.

	   At this point, only "HW VERSION" or "DOWNLOAD OS" commands
	   will work. So, issue one of them, and wait for TX
	   interrupt. This can take a *long* time after a cold boot,
	   while the ISC ROM does its RAM test. The SDK says up to 4
	   seconds - with 12MB of RAM on a Tropez+, it takes a lot
	   longer than that (~16secs). Note that the card understands
	   the difference between a warm and a cold boot, so
	   subsequent ISC2115 reboots (say, caused by module
	   reloading) will get through this much faster.

	   XXX Interesting question: why is no RX interrupt received first ?
	*/

	wavefront_should_cause_interrupt(dev, WFC_HARDWARE_VERSION, 
					 dev->data_port, ramcheck_time*HZ);

	if (!dev->irq_ok) {
		snd_printk ("post-RAM-check interrupt not received.\n");
		goto gone_bad;
	} 

	if (!wavefront_wait (dev, STAT_CAN_READ)) {
		snd_printk ("no response to HW version cmd.\n");
		goto gone_bad;
	}
	
	if ((hwv[0] = wavefront_read (dev)) == -1) {
		snd_printk ("board not responding correctly.\n");
		goto gone_bad;
	}

	if (hwv[0] == 0xFF) { /* NAK */

		/* Board's RAM test failed. Try to read error code,
		   and tell us about it either way.
		*/
		
		if ((hwv[0] = wavefront_read (dev)) == -1) {
			snd_printk ("on-board RAM test failed "
				    "(bad error code).\n");
		} else {
			snd_printk ("on-board RAM test failed "
				    "(error code: 0x%x).\n",
				hwv[0]);
		}
		goto gone_bad;
	}

	/* We're OK, just get the next byte of the HW version response */

	if ((hwv[1] = wavefront_read (dev)) == -1) {
		snd_printk ("incorrect h/w response.\n");
		goto gone_bad;
	}

	snd_printk ("hardware version %d.%d\n",
		    hwv[0], hwv[1]);

	return 0;


     gone_bad:
	return (1);
}