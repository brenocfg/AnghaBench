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
struct mtk_base_afe {int /*<<< orphan*/  dev; } ;
struct mt2701_i2s_path {int /*<<< orphan*/  asrco_ck; int /*<<< orphan*/ * hop_ck; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

int mt2701_afe_enable_i2s(struct mtk_base_afe *afe,
			  struct mt2701_i2s_path *i2s_path,
			  int dir)
{
	int ret;

	ret = clk_prepare_enable(i2s_path->asrco_ck);
	if (ret) {
		dev_err(afe->dev, "failed to enable ASRC clock %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(i2s_path->hop_ck[dir]);
	if (ret) {
		dev_err(afe->dev, "failed to enable I2S clock %d\n", ret);
		goto err_hop_ck;
	}

	return 0;

err_hop_ck:
	clk_disable_unprepare(i2s_path->asrco_ck);

	return ret;
}