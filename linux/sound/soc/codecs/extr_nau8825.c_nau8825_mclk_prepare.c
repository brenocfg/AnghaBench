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
struct nau8825 {unsigned int mclk_freq; int /*<<< orphan*/  dev; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 unsigned int clk_round_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nau8825_mclk_prepare(struct nau8825 *nau8825, unsigned int freq)
{
	int ret = 0;

	nau8825->mclk = devm_clk_get(nau8825->dev, "mclk");
	if (IS_ERR(nau8825->mclk)) {
		dev_info(nau8825->dev, "No 'mclk' clock found, assume MCLK is managed externally");
		return 0;
	}

	if (!nau8825->mclk_freq) {
		ret = clk_prepare_enable(nau8825->mclk);
		if (ret) {
			dev_err(nau8825->dev, "Unable to prepare codec mclk\n");
			return ret;
		}
	}

	if (nau8825->mclk_freq != freq) {
		freq = clk_round_rate(nau8825->mclk, freq);
		ret = clk_set_rate(nau8825->mclk, freq);
		if (ret) {
			dev_err(nau8825->dev, "Unable to set mclk rate\n");
			return ret;
		}
		nau8825->mclk_freq = freq;
	}

	return 0;
}