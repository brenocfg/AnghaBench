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
struct vb_device_info {int /*<<< orphan*/  P3c9; int /*<<< orphan*/  P3c8; int /*<<< orphan*/  P3c6; } ;

/* Variables and functions */
 unsigned short* XGINew_VGA_DAC ; 
 int /*<<< orphan*/  XGI_WriteDAC (unsigned short,unsigned short,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  outb (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGI_LoadDAC(struct vb_device_info *pVBInfo)
{
	unsigned short data, data2, i, k, m, n, o, si, di, bx, dl, al, ah, dh;
	const unsigned short *table = XGINew_VGA_DAC;

	outb(0xFF, pVBInfo->P3c6);
	outb(0x00, pVBInfo->P3c8);

	for (i = 0; i < 16; i++) {
		data = table[i];

		for (k = 0; k < 3; k++) {
			data2 = 0;

			if (data & 0x01)
				data2 = 0x2A;

			if (data & 0x02)
				data2 += 0x15;

			outb(data2, pVBInfo->P3c9);
			data >>= 2;
		}
	}

	for (i = 16; i < 32; i++) {
		data = table[i];

		for (k = 0; k < 3; k++)
			outb(data, pVBInfo->P3c9);
	}

	si = 32;

	for (m = 0; m < 9; m++) {
		di = si;
		bx = si + 0x04;
		dl = 0;

		for (n = 0; n < 3; n++) {
			for (o = 0; o < 5; o++) {
				dh = table[si];
				ah = table[di];
				al = table[bx];
				si++;
				XGI_WriteDAC(dl, ah, al, dh, pVBInfo);
			}

			si -= 2;

			for (o = 0; o < 3; o++) {
				dh = table[bx];
				ah = table[di];
				al = table[si];
				si--;
				XGI_WriteDAC(dl, ah, al, dh, pVBInfo);
			}

			dl++;
		}

		si += 5;
	}
}