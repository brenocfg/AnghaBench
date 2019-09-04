#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bits_per_pixel; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct stifb_info {TYPE_2__ info; } ;

/* Variables and functions */
#define  DISABLE 129 
#define  ENABLE 128 
 scalar_t__ IS_24_DEVICE (struct stifb_info*) ; 
 int /*<<< orphan*/  NGLE_LOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  NGLE_UNLOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  hyperUndoITE (struct stifb_info*) ; 
 int /*<<< orphan*/  ngleClearOverlayPlanes (struct stifb_info*,int,int) ; 
 int /*<<< orphan*/  ngleDepth24_ClearImagePlanes (struct stifb_info*) ; 
 int /*<<< orphan*/  ngleDepth8_ClearImagePlanes (struct stifb_info*) ; 
 int /*<<< orphan*/  ngleResetAttrPlanes (struct stifb_info*,unsigned int) ; 

__attribute__((used)) static void 
hyperResetPlanes(struct stifb_info *fb, int enable)
{
	unsigned int controlPlaneReg;

	NGLE_LOCK(fb);

	if (IS_24_DEVICE(fb))
		if (fb->info.var.bits_per_pixel == 32)
			controlPlaneReg = 0x04000F00;
		else
			controlPlaneReg = 0x00000F00;   /* 0x00000800 should be enough, but lets clear all 4 bits */
	else
		controlPlaneReg = 0x00000F00; /* 0x00000100 should be enough, but lets clear all 4 bits */

	switch (enable) {
	case ENABLE:
		/* clear screen */
		if (IS_24_DEVICE(fb))
			ngleDepth24_ClearImagePlanes(fb);
		else
			ngleDepth8_ClearImagePlanes(fb);

		/* Paint attribute planes for default case.
		 * On Hyperdrive, this means all windows using overlay cmap 0. */
		ngleResetAttrPlanes(fb, controlPlaneReg);

		/* clear overlay planes */
	        ngleClearOverlayPlanes(fb, 0xff, 255);

		/**************************************************
		 ** Also need to counteract ITE settings 
		 **************************************************/
		hyperUndoITE(fb);
		break;

	case DISABLE:
		/* clear screen */
		if (IS_24_DEVICE(fb))
			ngleDepth24_ClearImagePlanes(fb);
		else
			ngleDepth8_ClearImagePlanes(fb);
		ngleResetAttrPlanes(fb, controlPlaneReg);
		ngleClearOverlayPlanes(fb, 0xff, 0);
		break;

	case -1:	/* RESET */
		hyperUndoITE(fb);
		ngleResetAttrPlanes(fb, controlPlaneReg);
		break;
    	}
	
	NGLE_UNLOCK(fb);
}