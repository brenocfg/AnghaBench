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
typedef  int u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
#define  CLR_BIT 131 
#define  CLR_CLK 130 
 int /*<<< orphan*/  INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_device*,int /*<<< orphan*/ ,int) ; 
#define  SET_BIT 129 
#define  SET_CLK 128 
 int /*<<< orphan*/  nc_gpreg ; 
 int /*<<< orphan*/  nc_mbox1 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void S24C16_set_bit(struct sym_device *np, u_char write_bit, u_char *gpreg, 
			  int bit_mode)
{
	udelay(5);
	switch (bit_mode) {
	case SET_BIT:
		*gpreg |= write_bit;
		break;
	case CLR_BIT:
		*gpreg &= 0xfe;
		break;
	case SET_CLK:
		*gpreg |= 0x02;
		break;
	case CLR_CLK:
		*gpreg &= 0xfd;
		break;

	}
	OUTB(np, nc_gpreg, *gpreg);
	INB(np, nc_mbox1);
	udelay(5);
}