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
typedef  int u16 ;

/* Variables and functions */
 int SE2CLK ; 
 int SE2CS ; 
 int SE2DI ; 
 int SE2DO ; 
 scalar_t__ TUL_NVRAM ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_se2_instr (unsigned long,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void initio_se2_wr(unsigned long base, u8 addr, u16 val)
{
	u8 rb;
	u8 instr;
	int i;

	instr = (u8) (addr | 0x40);
	initio_se2_instr(base, instr);	/* WRITE INSTR */
	for (i = 15; i >= 0; i--) {
		if (val & 0x8000)
			outb(SE2CS | SE2DO, base + TUL_NVRAM);	/* -CLK+dataBit 1 */
		else
			outb(SE2CS, base + TUL_NVRAM);		/* -CLK+dataBit 0 */
		udelay(30);
		outb(SE2CS | SE2CLK, base + TUL_NVRAM);		/* +CLK */
		udelay(30);
		val <<= 1;
	}
	outb(SE2CS, base + TUL_NVRAM);				/* -CLK */
	udelay(30);
	outb(0, base + TUL_NVRAM);				/* -CS  */
	udelay(30);

	outb(SE2CS, base + TUL_NVRAM);				/* +CS  */
	udelay(30);

	for (;;) {
		outb(SE2CS | SE2CLK, base + TUL_NVRAM);		/* +CLK */
		udelay(30);
		outb(SE2CS, base + TUL_NVRAM);			/* -CLK */
		udelay(30);
		if ((rb = inb(base + TUL_NVRAM)) & SE2DI)
			break;	/* write complete */
	}
	outb(0, base + TUL_NVRAM);				/* -CS */
}