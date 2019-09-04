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
struct vb_device_info {int /*<<< orphan*/  P3da; } ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGI_WaitDisply(struct vb_device_info *pVBInfo)
{
	while ((inb(pVBInfo->P3da) & 0x01))
		break;

	while (!(inb(pVBInfo->P3da) & 0x01))
		break;
}