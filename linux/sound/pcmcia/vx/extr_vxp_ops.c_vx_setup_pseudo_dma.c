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
struct snd_vxpocket {int /*<<< orphan*/  regDIALOG; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIALOG ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  ICR_RREQ ; 
 int /*<<< orphan*/  ICR_TREQ ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  VXP_DLG_DMA16_SEL_MASK ; 
 int /*<<< orphan*/  VXP_DLG_DMAREAD_SEL_MASK ; 
 int /*<<< orphan*/  VXP_DLG_DMAWRITE_SEL_MASK ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int /*<<< orphan*/  vx_inb (struct snd_vxpocket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outb (struct snd_vxpocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vx_setup_pseudo_dma(struct vx_core *_chip, int do_write)
{
	struct snd_vxpocket *chip = to_vxpocket(_chip);

	/* Interrupt mode and HREQ pin enabled for host transmit / receive data transfers */
	vx_outb(chip, ICR, do_write ? ICR_TREQ : ICR_RREQ);
	/* Reset the pseudo-dma register */
	vx_inb(chip, ISR);
	vx_outb(chip, ISR, 0);

	/* Select DMA in read/write transfer mode and in 16-bit accesses */
	chip->regDIALOG |= VXP_DLG_DMA16_SEL_MASK;
	chip->regDIALOG |= do_write ? VXP_DLG_DMAWRITE_SEL_MASK : VXP_DLG_DMAREAD_SEL_MASK;
	vx_outb(chip, DIALOG, chip->regDIALOG);

}