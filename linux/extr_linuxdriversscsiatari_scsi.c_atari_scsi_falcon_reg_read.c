#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ fdc_acces_seccount; scalar_t__ dma_mode_status; } ;

/* Variables and functions */
 TYPE_1__ dma_wd ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static u8 atari_scsi_falcon_reg_read(unsigned int reg)
{
	unsigned long flags;
	u8 result;

	reg += 0x88;
	local_irq_save(flags);
	dma_wd.dma_mode_status = (u_short)reg;
	result = (u8)dma_wd.fdc_acces_seccount;
	local_irq_restore(flags);
	return result;
}