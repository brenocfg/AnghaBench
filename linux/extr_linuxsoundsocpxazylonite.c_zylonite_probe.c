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
struct snd_soc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_pout ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pout ; 

__attribute__((used)) static int zylonite_probe(struct snd_soc_card *card)
{
	int ret;

	if (clk_pout) {
		pout = clk_get(NULL, "CLK_POUT");
		if (IS_ERR(pout)) {
			dev_err(card->dev, "Unable to obtain CLK_POUT: %ld\n",
				PTR_ERR(pout));
			return PTR_ERR(pout);
		}

		ret = clk_enable(pout);
		if (ret != 0) {
			dev_err(card->dev, "Unable to enable CLK_POUT: %d\n",
				ret);
			clk_put(pout);
			return ret;
		}

		dev_dbg(card->dev, "MCLK enabled at %luHz\n",
			clk_get_rate(pout));
	}

	return 0;
}