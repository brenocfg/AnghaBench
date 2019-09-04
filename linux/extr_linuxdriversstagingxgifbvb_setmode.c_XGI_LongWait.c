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
struct vb_device_info {int /*<<< orphan*/  P3da; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGI_LongWait(struct vb_device_info *pVBInfo)
{
	unsigned short i;

	i = xgifb_reg_get(pVBInfo->P3c4, 0x1F);

	if (!(i & 0xC0)) {
		for (i = 0; i < 0xFFFF; i++) {
			if (!(inb(pVBInfo->P3da) & 0x08))
				break;
		}

		for (i = 0; i < 0xFFFF; i++) {
			if ((inb(pVBInfo->P3da) & 0x08))
				break;
		}
	}
}