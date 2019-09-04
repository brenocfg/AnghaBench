#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb_device_info {unsigned short TVInfo; int VBInfo; } ;
struct SiS_TVData {int dummy; } ;
struct TYPE_6__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short Ext_CRT2CRTC; } ;
struct TYPE_4__ {int MASK; unsigned short CAP; struct SiS_TVData const* DATAPTR; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 int SetInSlaveMode ; 
 unsigned short SetTVLockMode ; 
 unsigned short SetTVLowResolution ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_TVDataTable ; 

__attribute__((used)) static struct SiS_TVData const *XGI_GetTVPtr(
	unsigned short ModeIdIndex,
	unsigned short RefreshRateTableIndex,
	struct vb_device_info *pVBInfo)
{
	unsigned short i, tempdx, tempal, modeflag;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	tempal = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
	tempal = tempal & 0x3f;
	tempdx = pVBInfo->TVInfo;

	if (pVBInfo->VBInfo & SetInSlaveMode)
		tempdx = tempdx | SetTVLockMode;

	if (modeflag & HalfDCLK)
		tempdx = tempdx | SetTVLowResolution;

	i = 0;

	while (XGI_TVDataTable[i].MASK != 0xffff) {
		if ((tempdx & XGI_TVDataTable[i].MASK) ==
			XGI_TVDataTable[i].CAP)
			break;
		i++;
	}

	return &XGI_TVDataTable[i].DATAPTR[tempal];
}