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
typedef  int uint32_t ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int csio_rd_reg32 (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int) ; 

void
csio_set_reg_field(struct csio_hw *hw, uint32_t reg, uint32_t mask,
		   uint32_t value)
{
	uint32_t val = csio_rd_reg32(hw, reg) & ~mask;

	csio_wr_reg32(hw, val | value, reg);
	/* Flush */
	csio_rd_reg32(hw, reg);

}