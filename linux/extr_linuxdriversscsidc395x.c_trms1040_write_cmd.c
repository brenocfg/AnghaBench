#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;

/* Variables and functions */
 int NVR_BITOUT ; 
 int NVR_CLOCK ; 
 int NVR_SELECT ; 
 unsigned long TRM_S1040_GEN_NVRAM ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  trms1040_wait_30us (unsigned long) ; 

__attribute__((used)) static void trms1040_write_cmd(unsigned long io_port, u8 cmd, u8 addr)
{
	int i;
	u8 send_data;

	/* program SB + OP code */
	for (i = 0; i < 3; i++, cmd <<= 1) {
		send_data = NVR_SELECT;
		if (cmd & 0x04)	/* Start from bit 2 */
			send_data |= NVR_BITOUT;

		outb(send_data, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);
		outb((send_data | NVR_CLOCK),
		     io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);
	}

	/* send address */
	for (i = 0; i < 7; i++, addr <<= 1) {
		send_data = NVR_SELECT;
		if (addr & 0x40)	/* Start from bit 6 */
			send_data |= NVR_BITOUT;

		outb(send_data, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);
		outb((send_data | NVR_CLOCK),
		     io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);
	}
	outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_wait_30us(io_port);
}