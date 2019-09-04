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
struct mtk_base_afe {struct mt2701_afe_private* platform_priv; } ;
struct mt2701_afe_private {int /*<<< orphan*/  mrgif_ck; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

int mt2701_enable_btmrg_clk(struct mtk_base_afe *afe)
{
	struct mt2701_afe_private *afe_priv = afe->platform_priv;

	return clk_prepare_enable(afe_priv->mrgif_ck);
}