#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vb_device_info {int /*<<< orphan*/  P3c2; } ;
struct TYPE_2__ {int Ext_InfoFlag; } ;

/* Variables and functions */
 TYPE_1__* XGI330_RefIndex ; 
 int /*<<< orphan*/  outb (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGI_SetSync(unsigned short RefreshRateTableIndex,
			struct vb_device_info *pVBInfo)
{
	unsigned short sync, temp;

	/* di+0x00 */
	sync = XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag >> 8;
	sync &= 0xC0;
	temp = 0x2F;
	temp |= sync;
	outb(temp, pVBInfo->P3c2); /* Set Misc(3c2) */
}