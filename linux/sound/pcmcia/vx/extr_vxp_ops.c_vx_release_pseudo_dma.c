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
struct vx_core {int dummy; } ;
struct snd_vxpocket {int regDIALOG; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIALOG ; 
 int /*<<< orphan*/  ICR ; 
 int VXP_DLG_DMA16_SEL_MASK ; 
 int VXP_DLG_DMAREAD_SEL_MASK ; 
 int VXP_DLG_DMAWRITE_SEL_MASK ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outb (struct snd_vxpocket*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx_release_pseudo_dma(struct vx_core *_chip)
{
	struct snd_vxpocket *chip = to_vxpocket(_chip);

	/* Disable DMA and 16-bit accesses */
	chip->regDIALOG &= ~(VXP_DLG_DMAWRITE_SEL_MASK|
			     VXP_DLG_DMAREAD_SEL_MASK|
			     VXP_DLG_DMA16_SEL_MASK);
	vx_outb(chip, DIALOG, chip->regDIALOG);
	/* HREQ pin disabled. */
	vx_outb(chip, ICR, 0);
}