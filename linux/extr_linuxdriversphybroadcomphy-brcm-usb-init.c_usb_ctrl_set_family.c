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
typedef  size_t u32 ;
struct brcm_usb_init_params {size_t* usb_reg_bits_map; void* ctrl_regs; } ;

/* Variables and functions */
 size_t brcmusb_readl (void*) ; 
 int /*<<< orphan*/  brcmusb_writel (size_t,void*) ; 

__attribute__((used)) static inline
void usb_ctrl_set_family(struct brcm_usb_init_params *params,
			 u32 reg_offset, u32 field)
{
	u32 mask;
	void *reg;

	mask = params->usb_reg_bits_map[field];
	reg = params->ctrl_regs + reg_offset;
	brcmusb_writel(brcmusb_readl(reg) | mask, reg);
}