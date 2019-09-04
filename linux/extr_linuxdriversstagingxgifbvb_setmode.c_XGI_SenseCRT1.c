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
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; scalar_t__ P3c8; int /*<<< orphan*/  P3c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGI_WaitDisply (struct vb_device_info*) ; 
 unsigned short inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char) ; 

void XGI_SenseCRT1(struct vb_device_info *pVBInfo)
{
	unsigned char CRTCData[17] = { 0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81,
			0x0B, 0x3E, 0xE9, 0x0B, 0xDF, 0xE7, 0x04, 0x00, 0x00,
			0x05, 0x00 };

	unsigned char SR01 = 0, SR1F = 0, SR07 = 0, SR06 = 0;

	unsigned char CR17, CR63, SR31;
	unsigned short temp;

	int i;

	xgifb_reg_set(pVBInfo->P3c4, 0x05, 0x86);

	/* to fix XG42 single LCD sense to CRT+LCD */
	xgifb_reg_set(pVBInfo->P3d4, 0x57, 0x4A);
	xgifb_reg_set(pVBInfo->P3d4, 0x53, (xgifb_reg_get(
			pVBInfo->P3d4, 0x53) | 0x02));

	SR31 = xgifb_reg_get(pVBInfo->P3c4, 0x31);
	CR63 = xgifb_reg_get(pVBInfo->P3d4, 0x63);
	SR01 = xgifb_reg_get(pVBInfo->P3c4, 0x01);

	xgifb_reg_set(pVBInfo->P3c4, 0x01, (unsigned char)(SR01 & 0xDF));
	xgifb_reg_set(pVBInfo->P3d4, 0x63, (unsigned char)(CR63 & 0xBF));

	CR17 = xgifb_reg_get(pVBInfo->P3d4, 0x17);
	xgifb_reg_set(pVBInfo->P3d4, 0x17, (unsigned char)(CR17 | 0x80));

	SR1F = xgifb_reg_get(pVBInfo->P3c4, 0x1F);
	xgifb_reg_set(pVBInfo->P3c4, 0x1F, (unsigned char)(SR1F | 0x04));

	SR07 = xgifb_reg_get(pVBInfo->P3c4, 0x07);
	xgifb_reg_set(pVBInfo->P3c4, 0x07, (unsigned char)(SR07 & 0xFB));
	SR06 = xgifb_reg_get(pVBInfo->P3c4, 0x06);
	xgifb_reg_set(pVBInfo->P3c4, 0x06, (unsigned char)(SR06 & 0xC3));

	xgifb_reg_set(pVBInfo->P3d4, 0x11, 0x00);

	for (i = 0; i < 8; i++)
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)i, CRTCData[i]);

	for (i = 8; i < 11; i++)
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)(i + 8),
			      CRTCData[i]);

	for (i = 11; i < 13; i++)
		xgifb_reg_set(pVBInfo->P3d4, (unsigned short)(i + 4),
			      CRTCData[i]);

	for (i = 13; i < 16; i++)
		xgifb_reg_set(pVBInfo->P3c4, (unsigned short)(i - 3),
			      CRTCData[i]);

	xgifb_reg_set(pVBInfo->P3c4, 0x0E, (unsigned char)(CRTCData[16]
		      & 0xE0));

	xgifb_reg_set(pVBInfo->P3c4, 0x31, 0x00);
	xgifb_reg_set(pVBInfo->P3c4, 0x2B, 0x1B);
	xgifb_reg_set(pVBInfo->P3c4, 0x2C, 0xE1);

	outb(0x00, pVBInfo->P3c8);

	for (i = 0; i < 256 * 3; i++)
		outb(0x0F, (pVBInfo->P3c8 + 1)); /* DAC_TEST_PARMS */

	mdelay(1);

	XGI_WaitDisply(pVBInfo);
	temp = inb(pVBInfo->P3c2);

	if (temp & 0x10)
		xgifb_reg_and_or(pVBInfo->P3d4, 0x32, 0xDF, 0x20);
	else
		xgifb_reg_and_or(pVBInfo->P3d4, 0x32, 0xDF, 0x00);

	/* avoid display something, set BLACK DAC if not restore DAC */
	outb(0x00, pVBInfo->P3c8);

	for (i = 0; i < 256 * 3; i++)
		outb(0, (pVBInfo->P3c8 + 1));

	xgifb_reg_set(pVBInfo->P3c4, 0x01, SR01);
	xgifb_reg_set(pVBInfo->P3d4, 0x63, CR63);
	xgifb_reg_set(pVBInfo->P3c4, 0x31, SR31);

	xgifb_reg_set(pVBInfo->P3d4, 0x53, (xgifb_reg_get(
			pVBInfo->P3d4, 0x53) & 0xFD));
	xgifb_reg_set(pVBInfo->P3c4, 0x1F, (unsigned char)SR1F);
}