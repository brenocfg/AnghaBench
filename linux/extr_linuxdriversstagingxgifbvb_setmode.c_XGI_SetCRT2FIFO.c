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
struct vb_device_info {int /*<<< orphan*/  Part1Port; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void XGI_SetCRT2FIFO(struct vb_device_info *pVBInfo)
{
	/* threshold high ,disable auto threshold */
	xgifb_reg_set(pVBInfo->Part1Port, 0x01, 0x3B);
	/* threshold low default 04h */
	xgifb_reg_and_or(pVBInfo->Part1Port, 0x02, ~(0x3F), 0x04);
}