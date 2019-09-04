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
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned char XGINew_CheckFrequence(struct vb_device_info *pVBInfo)
{
	unsigned char data;

	data = xgifb_reg_get(pVBInfo->P3d4, 0x97);

	if ((data & 0x10) == 0) {
		data = xgifb_reg_get(pVBInfo->P3c4, 0x39);
		return (data & 0x02) >> 1;
	}
	return data & 0x01;
}