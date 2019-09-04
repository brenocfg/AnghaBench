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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 size_t MTK_REG_MTK_INT_STATUS ; 
 size_t MTK_REG_MTK_INT_STATUS2 ; 
 size_t mtk_reg_r32 (struct mtk_eth*,size_t) ; 
 scalar_t__* mtk_reg_table ; 

__attribute__((used)) static u32 mtk_irq_pending_status(struct mtk_eth *eth)
{
	u32 status_reg = MTK_REG_MTK_INT_STATUS;

	if (mtk_reg_table[MTK_REG_MTK_INT_STATUS2])
		status_reg = MTK_REG_MTK_INT_STATUS2;

	return mtk_reg_r32(eth, status_reg);
}