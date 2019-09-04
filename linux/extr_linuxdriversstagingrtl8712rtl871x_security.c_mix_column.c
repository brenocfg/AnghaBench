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
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  xor_32 (int*,int*,int*) ; 

__attribute__((used)) static void mix_column(u8 *in, u8 *out)
{
	sint i;
	u8 add1b[4];
	u8 add1bf7[4];
	u8 rotl[4];
	u8 swap_halves[4];
	u8 andf7[4];
	u8 rotr[4];
	u8 temp[4];
	u8 tempb[4];

	for (i = 0; i < 4; i++) {
		if ((in[i] & 0x80) == 0x80)
			add1b[i] = 0x1b;
		else
			add1b[i] = 0x00;
	}
	swap_halves[0] = in[2];    /* Swap halves */
	swap_halves[1] = in[3];
	swap_halves[2] = in[0];
	swap_halves[3] = in[1];
	rotl[0] = in[3];        /* Rotate left 8 bits */
	rotl[1] = in[0];
	rotl[2] = in[1];
	rotl[3] = in[2];
	andf7[0] = in[0] & 0x7f;
	andf7[1] = in[1] & 0x7f;
	andf7[2] = in[2] & 0x7f;
	andf7[3] = in[3] & 0x7f;
	for (i = 3; i > 0; i--) {   /* logical shift left 1 bit */
		andf7[i] = andf7[i] << 1;
		if ((andf7[i - 1] & 0x80) == 0x80)
			andf7[i] = (andf7[i] | 0x01);
	}
	andf7[0] = andf7[0] << 1;
	andf7[0] = andf7[0] & 0xfe;
	xor_32(add1b, andf7, add1bf7);
	xor_32(in, add1bf7, rotr);
	temp[0] = rotr[0];         /* Rotate right 8 bits */
	rotr[0] = rotr[1];
	rotr[1] = rotr[2];
	rotr[2] = rotr[3];
	rotr[3] = temp[0];
	xor_32(add1bf7, rotr, temp);
	xor_32(swap_halves, rotl, tempb);
	xor_32(temp, tempb, out);
}