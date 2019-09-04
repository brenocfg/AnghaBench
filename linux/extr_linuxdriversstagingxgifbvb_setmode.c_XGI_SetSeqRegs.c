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
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;
struct TYPE_2__ {unsigned char* SR; } ;

/* Variables and functions */
 TYPE_1__ XGI330_StandTable ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void XGI_SetSeqRegs(struct vb_device_info *pVBInfo)
{
	unsigned char SRdata, i;

	xgifb_reg_set(pVBInfo->P3c4, 0x00, 0x03); /* Set SR0 */

	for (i = 0; i < 4; i++) {
		/* Get SR1,2,3,4 from file */
		/* SR1 is with screen off 0x20 */
		SRdata = XGI330_StandTable.SR[i];
		/* Set SR 1 2 3 4 */
		xgifb_reg_set(pVBInfo->P3c4, i + 1, SRdata);
	}
}