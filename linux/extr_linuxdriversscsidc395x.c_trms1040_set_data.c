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
 int NVR_BITIN ; 
 int NVR_BITOUT ; 
 int NVR_CLOCK ; 
 int NVR_SELECT ; 
 unsigned long TRM_S1040_GEN_NVRAM ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  trms1040_wait_30us (unsigned long) ; 
 int /*<<< orphan*/  trms1040_write_cmd (unsigned long,int,int) ; 

__attribute__((used)) static void trms1040_set_data(unsigned long io_port, u8 addr, u8 byte)
{
	int i;
	u8 send_data;

	/* Send write command & address */
	trms1040_write_cmd(io_port, 0x05, addr);

	/* Write data */
	for (i = 0; i < 8; i++, byte <<= 1) {
		send_data = NVR_SELECT;
		if (byte & 0x80)	/* Start from bit 7 */
			send_data |= NVR_BITOUT;

		outb(send_data, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);
		outb((send_data | NVR_CLOCK), io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);
	}
	outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_wait_30us(io_port);

	/* Disable chip select */
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_wait_30us(io_port);

	outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_wait_30us(io_port);

	/* Wait for write ready */
	while (1) {
		outb((NVR_SELECT | NVR_CLOCK), io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);

		outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_wait_30us(io_port);

		if (inb(io_port + TRM_S1040_GEN_NVRAM) & NVR_BITIN)
			break;
	}

	/*  Disable chip select */
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
}