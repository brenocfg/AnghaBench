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
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;
struct mt2701_i2s_path {scalar_t__* on; struct mt2701_i2s_data** i2s_data; } ;
struct mt2701_i2s_data {int /*<<< orphan*/  i2s_ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYS_I2S_CON_I2S_EN ; 
 int /*<<< orphan*/  mt2701_afe_disable_i2s (struct mtk_base_afe*,struct mt2701_i2s_path*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt2701_afe_i2s_path_disable(struct mtk_base_afe *afe,
				       struct mt2701_i2s_path *i2s_path,
				       int stream_dir)
{
	const struct mt2701_i2s_data *i2s_data = i2s_path->i2s_data[stream_dir];

	if (--i2s_path->on[stream_dir] < 0)
		i2s_path->on[stream_dir] = 0;

	if (i2s_path->on[stream_dir])
		return 0;

	/* disable i2s */
	regmap_update_bits(afe->regmap, i2s_data->i2s_ctrl_reg,
			   ASYS_I2S_CON_I2S_EN, 0);

	mt2701_afe_disable_i2s(afe, i2s_path, stream_dir);

	return 0;
}