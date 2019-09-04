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
struct vb_device_info {unsigned long P3c4; unsigned long P3d4; unsigned long P3c0; unsigned long P3ce; unsigned long P3c2; unsigned long P3cc; unsigned long P3ca; unsigned long P3c6; unsigned long P3c7; unsigned long P3c8; unsigned long P3c9; unsigned long P3da; void* Part5Port; void* Part4Port; scalar_t__ Part3Port; scalar_t__ Part2Port; scalar_t__ Part1Port; scalar_t__ Part0Port; } ;

/* Variables and functions */
 scalar_t__ SIS_CRT2_PORT_04 ; 
 scalar_t__ SIS_CRT2_PORT_10 ; 
 scalar_t__ SIS_CRT2_PORT_12 ; 
 void* SIS_CRT2_PORT_14 ; 
 scalar_t__ XGI_CRT2_PORT_00 ; 

void XGIRegInit(struct vb_device_info *XGI_Pr, unsigned long BaseAddr)
{
	XGI_Pr->P3c4 = BaseAddr + 0x14;
	XGI_Pr->P3d4 = BaseAddr + 0x24;
	XGI_Pr->P3c0 = BaseAddr + 0x10;
	XGI_Pr->P3ce = BaseAddr + 0x1e;
	XGI_Pr->P3c2 = BaseAddr + 0x12;
	XGI_Pr->P3cc = BaseAddr + 0x1c;
	XGI_Pr->P3ca = BaseAddr + 0x1a;
	XGI_Pr->P3c6 = BaseAddr + 0x16;
	XGI_Pr->P3c7 = BaseAddr + 0x17;
	XGI_Pr->P3c8 = BaseAddr + 0x18;
	XGI_Pr->P3c9 = BaseAddr + 0x19;
	XGI_Pr->P3da = BaseAddr + 0x2A;
	XGI_Pr->Part0Port = BaseAddr + XGI_CRT2_PORT_00;
	/* Digital video interface registers (LCD) */
	XGI_Pr->Part1Port = BaseAddr + SIS_CRT2_PORT_04;
	/* 301 TV Encoder registers */
	XGI_Pr->Part2Port = BaseAddr + SIS_CRT2_PORT_10;
	/* 301 Macrovision registers */
	XGI_Pr->Part3Port = BaseAddr + SIS_CRT2_PORT_12;
	/* 301 VGA2 (and LCD) registers */
	XGI_Pr->Part4Port = BaseAddr + SIS_CRT2_PORT_14;
	/* 301 palette address port registers */
	XGI_Pr->Part5Port = BaseAddr + SIS_CRT2_PORT_14 + 2;
}