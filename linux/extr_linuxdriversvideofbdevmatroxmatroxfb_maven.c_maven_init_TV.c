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
struct mavenregs {scalar_t__ mode; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LR (int) ; 
 int /*<<< orphan*/  LRP (int) ; 
 scalar_t__ MATROXFB_OUTPUT_MODE_PAL ; 
 int maven_get_reg (struct i2c_client*,int) ; 
 int /*<<< orphan*/  maven_set_reg (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  maven_set_reg_pair (struct i2c_client*,int,int) ; 

__attribute__((used)) static void maven_init_TV(struct i2c_client* c, const struct mavenregs* m) {
	int val;


	maven_set_reg(c, 0x3E, 0x01);
	maven_get_reg(c, 0x82);	/* fetch oscillator state? */
	maven_set_reg(c, 0x8C, 0x00);
	maven_get_reg(c, 0x94);	/* get 0x82 */
	maven_set_reg(c, 0x94, 0xA2);
	/* xmiscctrl */

	maven_set_reg_pair(c, 0x8E, 0x1EFF);
	maven_set_reg(c, 0xC6, 0x01);

	/* removed code... */

	maven_get_reg(c, 0x06);
	maven_set_reg(c, 0x06, 0xF9);	/* or read |= 0xF0 ? */

	/* removed code here... */

	/* real code begins here? */
	/* chroma subcarrier */
	LR(0x00); LR(0x01); LR(0x02); LR(0x03);

	LR(0x04);

	LR(0x2C);
	LR(0x08);
	LR(0x0A);
	LR(0x09);
	LR(0x29);
	LRP(0x31);
	LRP(0x17);
	LR(0x0B);
	LR(0x0C);
	if (m->mode == MATROXFB_OUTPUT_MODE_PAL) {
		maven_set_reg(c, 0x35, 0x10); /* ... */
	} else {
		maven_set_reg(c, 0x35, 0x0F); /* ... */
	}

	LRP(0x10);

	LRP(0x0E);
	LRP(0x1E);

	LR(0x20);	/* saturation #1 */
	LR(0x22);	/* saturation #2 */
	LR(0x25);	/* hue */
	LR(0x34);
	LR(0x33);
	LR(0x19);
	LR(0x12);
	LR(0x3B);
	LR(0x13);
	LR(0x39);
	LR(0x1D);
	LR(0x3A);
	LR(0x24);
	LR(0x14);
	LR(0x15);
	LR(0x16);
	LRP(0x2D);
	LRP(0x2F);
	LR(0x1A);
	LR(0x1B);
	LR(0x1C);
	LR(0x23);
	LR(0x26);
	LR(0x28);
	LR(0x27);
	LR(0x21);
	LRP(0x2A);
	if (m->mode == MATROXFB_OUTPUT_MODE_PAL)
		maven_set_reg(c, 0x35, 0x1D);	/* ... */
	else
		maven_set_reg(c, 0x35, 0x1C);

	LRP(0x3C);
	LR(0x37);
	LR(0x38);
	maven_set_reg(c, 0xB3, 0x01);

	maven_get_reg(c, 0xB0);	/* read 0x80 */
	maven_set_reg(c, 0xB0, 0x08);	/* ugh... */
	maven_get_reg(c, 0xB9);	/* read 0x7C */
	maven_set_reg(c, 0xB9, 0x78);
	maven_get_reg(c, 0xBF);	/* read 0x00 */
	maven_set_reg(c, 0xBF, 0x02);
	maven_get_reg(c, 0x94);	/* read 0x82 */
	maven_set_reg(c, 0x94, 0xB3);

	LR(0x80); /* 04 1A 91 or 05 21 91 */
	LR(0x81);
	LR(0x82);

	maven_set_reg(c, 0x8C, 0x20);
	maven_get_reg(c, 0x8D);
	maven_set_reg(c, 0x8D, 0x10);

	LR(0x90); /* 4D 50 52 or 4E 05 45 */
	LR(0x91);
	LR(0x92);

	LRP(0x9A); /* 0049 or 004F */
	LRP(0x9C); /* 0004 or 0004 */
	LRP(0x9E); /* 0458 or 045E */
	LRP(0xA0); /* 05DA or 051B */
	LRP(0xA2); /* 00CC or 00CF */
	LRP(0xA4); /* 007D or 007F */
	LRP(0xA6); /* 007C or 007E */
	LRP(0xA8); /* 03CB or 03CE */
	LRP(0x98); /* 0000 or 0000 */
	LRP(0xAE); /* 0044 or 003A */
	LRP(0x96); /* 05DA or 051B */
	LRP(0xAA); /* 04BC or 046A */
	LRP(0xAC); /* 004D or 004E */

	LR(0xBE);
	LR(0xC2);

	maven_get_reg(c, 0x8D);
	maven_set_reg(c, 0x8D, 0x04);

	LR(0x20);	/* saturation #1 */
	LR(0x22);	/* saturation #2 */
	LR(0x93);	/* whoops */
	LR(0x20);	/* oh, saturation #1 again */
	LR(0x22);	/* oh, saturation #2 again */
	LR(0x25);	/* hue */
	LRP(0x0E);
	LRP(0x1E);
	LRP(0x0E);	/* problems with memory? */
	LRP(0x1E);	/* yes, matrox must have problems in memory area... */

	/* load gamma correction stuff */
	LR(0x83);
	LR(0x84);
	LR(0x85);
	LR(0x86);
	LR(0x87);
	LR(0x88);
	LR(0x89);
	LR(0x8A);
	LR(0x8B);

	val = maven_get_reg(c, 0x8D);
	val &= 0x14;			/* 0x10 or anything ored with it */
	maven_set_reg(c, 0x8D, val);

	LR(0x33);
	LR(0x19);
	LR(0x12);
	LR(0x3B);
	LR(0x13);
	LR(0x39);
	LR(0x1D);
	LR(0x3A);
	LR(0x24);
	LR(0x14);
	LR(0x15);
	LR(0x16);
	LRP(0x2D);
	LRP(0x2F);
	LR(0x1A);
	LR(0x1B);
	LR(0x1C);
	LR(0x23);
	LR(0x26);
	LR(0x28);
	LR(0x27);
	LR(0x21);
	LRP(0x2A);
	if (m->mode == MATROXFB_OUTPUT_MODE_PAL)
		maven_set_reg(c, 0x35, 0x1D);
	else
		maven_set_reg(c, 0x35, 0x1C);
	LRP(0x3C);
	LR(0x37);
	LR(0x38);

	maven_get_reg(c, 0xB0);
	LR(0xB0);	/* output mode */
	LR(0x90);
	LR(0xBE);
	LR(0xC2);

	LRP(0x9A);
	LRP(0xA2);
	LRP(0x9E);
	LRP(0xA6);
	LRP(0xAA);
	LRP(0xAC);
	maven_set_reg(c, 0x3E, 0x00);
	maven_set_reg(c, 0x95, 0x20);
}