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
struct vb_device_info {scalar_t__ ModeType; int VBInfo; } ;

/* Variables and functions */
 int DisableCRT2Display ; 
 int LoadDACFlag ; 
 scalar_t__ ModeVGA ; 
 int SetInSlaveMode ; 
 int /*<<< orphan*/  XGINew_EnableCRT2 (struct vb_device_info*) ; 

__attribute__((used)) static void XGI_SetGroup5(struct vb_device_info *pVBInfo)
{
	if (pVBInfo->ModeType == ModeVGA) {
		if (!(pVBInfo->VBInfo & (SetInSlaveMode | LoadDACFlag
				| DisableCRT2Display))) {
			XGINew_EnableCRT2(pVBInfo);
		}
	}
}