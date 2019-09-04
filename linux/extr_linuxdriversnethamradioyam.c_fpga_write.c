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

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LSR (int) ; 
 int LSR_TSRE ; 
 int /*<<< orphan*/  MCR (int) ; 
 unsigned char MCR_DTR ; 
 unsigned char MCR_OUT1 ; 
 unsigned char MCR_OUT2 ; 
 unsigned char MCR_RTS ; 
 int /*<<< orphan*/  THR (int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int fpga_write(int iobase, unsigned char wrd)
{
	unsigned char bit;
	int k;
	unsigned long timeout = jiffies + HZ / 10;

	for (k = 0; k < 8; k++) {
		bit = (wrd & 0x80) ? (MCR_RTS | MCR_DTR) : MCR_DTR;
		outb(bit | MCR_OUT1 | MCR_OUT2, MCR(iobase));
		wrd <<= 1;
		outb(0xfc, THR(iobase));
		while ((inb(LSR(iobase)) & LSR_TSRE) == 0)
			if (time_after(jiffies, timeout))
				return -1;
	}

	return 0;
}