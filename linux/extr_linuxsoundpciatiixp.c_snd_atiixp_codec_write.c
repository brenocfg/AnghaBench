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
struct atiixp {int dummy; } ;

/* Variables and functions */
 unsigned int ATI_REG_PHYS_OUT_ADDR_EN ; 
 unsigned int ATI_REG_PHYS_OUT_ADDR_SHIFT ; 
 unsigned int ATI_REG_PHYS_OUT_DATA_SHIFT ; 
 int /*<<< orphan*/  PHYS_OUT_ADDR ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ snd_atiixp_acquire_codec (struct atiixp*) ; 

__attribute__((used)) static void snd_atiixp_codec_write(struct atiixp *chip, unsigned short codec,
				   unsigned short reg, unsigned short val)
{
	unsigned int data;
    
	if (snd_atiixp_acquire_codec(chip) < 0)
		return;
	data = ((unsigned int)val << ATI_REG_PHYS_OUT_DATA_SHIFT) |
		((unsigned int)reg << ATI_REG_PHYS_OUT_ADDR_SHIFT) |
		ATI_REG_PHYS_OUT_ADDR_EN | codec;
	atiixp_write(chip, PHYS_OUT_ADDR, data);
}