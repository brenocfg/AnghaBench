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
struct mtk_base_afe {struct mt8183_afe_private* platform_priv; } ;
struct mt8183_afe_private {int /*<<< orphan*/ * clk; } ;
struct TYPE_2__ {int m_sel_id; int div_clk_id; } ;

/* Variables and functions */
 int MT8183_I2S5_MCK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 TYPE_1__* mck_div ; 

void mt8183_mck_disable(struct mtk_base_afe *afe, int mck_id)
{
	struct mt8183_afe_private *afe_priv = afe->platform_priv;
	int m_sel_id = mck_div[mck_id].m_sel_id;
	int div_clk_id = mck_div[mck_id].div_clk_id;

	/* i2s5 mck not support */
	if (mck_id == MT8183_I2S5_MCK)
		return;

	clk_disable_unprepare(afe_priv->clk[div_clk_id]);
	if (m_sel_id >= 0)
		clk_disable_unprepare(afe_priv->clk[m_sel_id]);
}