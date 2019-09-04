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
struct vx_pipe {int hw_ptr; int buffer_bytes; } ;
struct vx_core {int dummy; } ;
struct snd_vxpocket {int /*<<< orphan*/  regDIALOG; } ;
struct snd_pcm_runtime {scalar_t__ dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIALOG ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  VXP_DLG_DMA16_SEL_MASK ; 
 int /*<<< orphan*/  VXP_DLG_DMAREAD_SEL_MASK ; 
 int /*<<< orphan*/  VX_DMA ; 
 void* inw (long) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_setup_pseudo_dma (struct vx_core*,int /*<<< orphan*/ ) ; 
 long vxp_reg_addr (struct vx_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxp_dma_read(struct vx_core *chip, struct snd_pcm_runtime *runtime,
			 struct vx_pipe *pipe, int count)
{
	struct snd_vxpocket *pchip = to_vxpocket(chip);
	long port = vxp_reg_addr(chip, VX_DMA);
	int offset = pipe->hw_ptr;
	unsigned short *addr = (unsigned short *)(runtime->dma_area + offset);

	if (snd_BUG_ON(count % 2))
		return;
	vx_setup_pseudo_dma(chip, 0);
	if (offset + count >= pipe->buffer_bytes) {
		int length = pipe->buffer_bytes - offset;
		count -= length;
		length >>= 1; /* in 16bit words */
		/* Transfer using pseudo-dma. */
		for (; length > 0; length--)
			*addr++ = inw(port);
		addr = (unsigned short *)runtime->dma_area;
		pipe->hw_ptr = 0;
	}
	pipe->hw_ptr += count;
	count >>= 1; /* in 16bit words */
	/* Transfer using pseudo-dma. */
	for (; count > 1; count--)
		*addr++ = inw(port);
	/* Disable DMA */
	pchip->regDIALOG &= ~VXP_DLG_DMAREAD_SEL_MASK;
	vx_outb(chip, DIALOG, pchip->regDIALOG);
	/* Read the last word (16 bits) */
	*addr = inw(port);
	/* Disable 16-bit accesses */
	pchip->regDIALOG &= ~VXP_DLG_DMA16_SEL_MASK;
	vx_outb(chip, DIALOG, pchip->regDIALOG);
	/* HREQ pin disabled. */
	vx_outb(chip, ICR, 0);
}