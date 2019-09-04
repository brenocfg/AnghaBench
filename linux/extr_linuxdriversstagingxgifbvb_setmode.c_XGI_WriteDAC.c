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
struct vb_device_info {int /*<<< orphan*/  P3c9; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (unsigned short,unsigned short) ; 

__attribute__((used)) static void XGI_WriteDAC(unsigned short dl,
			 unsigned short ah,
			 unsigned short al,
			 unsigned short dh,
			 struct vb_device_info *pVBInfo)
{
	unsigned short bh, bl;

	bh = ah;
	bl = al;

	if (dl != 0) {
		swap(bh, dh);
		if (dl == 1)
			swap(bl, dh);
		else
			swap(bl, bh);
	}
	outb((unsigned short)dh, pVBInfo->P3c9);
	outb((unsigned short)bh, pVBInfo->P3c9);
	outb((unsigned short)bl, pVBInfo->P3c9);
}