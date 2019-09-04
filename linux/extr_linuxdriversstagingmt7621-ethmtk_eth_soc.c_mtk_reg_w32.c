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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_eth {int dummy; } ;
typedef  enum mtk_reg { ____Placeholder_mtk_reg } mtk_reg ;

/* Variables and functions */
 int /*<<< orphan*/ * mtk_reg_table ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_reg_w32(struct mtk_eth *eth, u32 val, enum mtk_reg reg)
{
	mtk_w32(eth, val, mtk_reg_table[reg]);
}