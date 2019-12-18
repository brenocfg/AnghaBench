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
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int UCHAR ;

/* Variables and functions */

void kuhl_m_sr98_noralsy_blocks(ULONG blocks[4], ULONG CardNumber, USHORT Year)
{
	UCHAR r1, r2, r3, r4, r5, r6, r7, y1, y2, c;
	r1 = (UCHAR) (CardNumber / 1000000);
	r2 = (UCHAR) ((CardNumber % 1000000) / 100000);
	r3 = (UCHAR) ((CardNumber % 100000) / 10000);
	r4 = (UCHAR) ((CardNumber % 10000) / 1000);
	r5 = (UCHAR) ((CardNumber % 1000) / 100);
	r6 = (UCHAR) ((CardNumber % 100) / 10);
	r7 = (UCHAR) (CardNumber % 10);
	y1 = (UCHAR) ((Year % 100) / 10);
	y2 = (UCHAR) (Year % 10);
	c = r1 ^ r2 ^ r3 ^ y1 ^ y2 ^ 0 ^ r4 ^ r5 ^ r6 ^ r7;
	blocks[0] = 0x00088068; // RF/32, Manchester, [1-3];
	blocks[1] = 0xbb0214ff;
	blocks[2] = (r1 << 28) | (r2 << 24) | (r3 << 20) | (y1 << 16) | (y2 << 12) | (r4 << 4) | r5;
	blocks[3] = (r6 << 28) | (r7 << 24) | (c << 20) | (7 << 16); // 7 = 0xb ^ 0xb ^ 0x0 ^ 0x2 ^ 0x1 ^ 0x4 ^ 0xf ^ 0xf (^ c1 ^ c1);
}