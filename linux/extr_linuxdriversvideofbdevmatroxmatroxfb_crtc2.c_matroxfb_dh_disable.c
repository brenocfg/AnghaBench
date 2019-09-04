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
struct matroxfb_dh_fb_info {struct matrox_fb_info* primary_dev; } ;
struct TYPE_3__ {int ctl; } ;
struct TYPE_4__ {TYPE_1__ crtc2; } ;
struct matrox_fb_info {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  mga_outl (int,int) ; 

__attribute__((used)) static void matroxfb_dh_disable(struct matroxfb_dh_fb_info* m2info) {
	struct matrox_fb_info *minfo = m2info->primary_dev;

	mga_outl(0x3C10, 0x00000004);	/* disable CRTC2, CRTC1->DAC1, PLL as clock source */
	minfo->hw.crtc2.ctl = 0x00000004;
}