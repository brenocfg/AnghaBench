#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_base_afe {int /*<<< orphan*/  dev; struct mt8183_afe_private* platform_priv; } ;
struct mtk_afe_i2s_priv {int dummy; } ;
struct mt8183_afe_private {struct mtk_afe_i2s_priv** dai_priv; } ;
struct TYPE_3__ {size_t id; } ;

/* Variables and functions */
 int DAI_I2S_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mtk_afe_i2s_priv* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct mtk_afe_i2s_priv*,TYPE_1__*,int) ; 
 TYPE_1__* mt8183_i2s_priv ; 

__attribute__((used)) static int mt8183_dai_i2s_set_priv(struct mtk_base_afe *afe)
{
	struct mt8183_afe_private *afe_priv = afe->platform_priv;
	struct mtk_afe_i2s_priv *i2s_priv;
	int i;

	for (i = 0; i < DAI_I2S_NUM; i++) {
		i2s_priv = devm_kzalloc(afe->dev,
					sizeof(struct mtk_afe_i2s_priv),
					GFP_KERNEL);
		if (!i2s_priv)
			return -ENOMEM;

		memcpy(i2s_priv, &mt8183_i2s_priv[i],
		       sizeof(struct mtk_afe_i2s_priv));

		afe_priv->dai_priv[mt8183_i2s_priv[i].id] = i2s_priv;
	}

	return 0;
}