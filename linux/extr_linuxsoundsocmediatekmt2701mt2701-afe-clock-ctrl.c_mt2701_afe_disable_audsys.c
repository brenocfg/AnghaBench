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
struct mt2701_afe_private {int /*<<< orphan*/ * base_ck; } ;

/* Variables and functions */
 size_t MT2701_AUDSYS_A1SYS ; 
 size_t MT2701_AUDSYS_A2SYS ; 
 size_t MT2701_AUDSYS_AFE ; 
 size_t MT2701_AUDSYS_AFE_CONN ; 
 size_t MT2701_INFRA_SYS_AUDIO ; 
 size_t MT2701_TOP_AUD_A1SYS ; 
 size_t MT2701_TOP_AUD_A2SYS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt2701_afe_disable_audsys(struct mtk_base_afe *afe)
{
	struct mt2701_afe_private *afe_priv = afe->platform_priv;

	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_AFE_CONN]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_A2SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_A1SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_AUDSYS_AFE]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_TOP_AUD_A1SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_TOP_AUD_A2SYS]);
	clk_disable_unprepare(afe_priv->base_ck[MT2701_INFRA_SYS_AUDIO]);
}