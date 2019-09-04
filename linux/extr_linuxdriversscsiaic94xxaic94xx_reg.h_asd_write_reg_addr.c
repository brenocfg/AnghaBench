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
typedef  scalar_t__ u32 ;
struct asd_ha_struct {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_BUSADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASD_BUSADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void asd_write_reg_addr(struct asd_ha_struct *asd_ha, u32 reg,
				      dma_addr_t dma_handle)
{
	asd_write_reg_dword(asd_ha, reg,   ASD_BUSADDR_LO(dma_handle));
	asd_write_reg_dword(asd_ha, reg+4, ASD_BUSADDR_HI(dma_handle));
}