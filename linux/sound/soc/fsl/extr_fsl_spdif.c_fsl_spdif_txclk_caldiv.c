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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct fsl_spdif_priv {int* txclk_df; int* sysclk_df; int* txrate; int /*<<< orphan*/  sysclk; } ;
struct clk {int dummy; } ;
typedef  enum spdif_txrate { ____Placeholder_spdif_txrate } spdif_txrate ;

/* Variables and functions */
 int clk_get_rate (struct clk*) ; 
 int clk_is_match (struct clk*,int /*<<< orphan*/ ) ; 
 int clk_round_rate (struct clk*,int) ; 
 int /*<<< orphan*/  do_div (int,int const) ; 

__attribute__((used)) static u32 fsl_spdif_txclk_caldiv(struct fsl_spdif_priv *spdif_priv,
				struct clk *clk, u64 savesub,
				enum spdif_txrate index, bool round)
{
	static const u32 rate[] = { 32000, 44100, 48000, 96000, 192000 };
	bool is_sysclk = clk_is_match(clk, spdif_priv->sysclk);
	u64 rate_ideal, rate_actual, sub;
	u32 arate;
	u16 sysclk_dfmin, sysclk_dfmax, sysclk_df;
	u8 txclk_df;

	/* The sysclk has an extra divisor [2, 512] */
	sysclk_dfmin = is_sysclk ? 2 : 1;
	sysclk_dfmax = is_sysclk ? 512 : 1;

	for (sysclk_df = sysclk_dfmin; sysclk_df <= sysclk_dfmax; sysclk_df++) {
		for (txclk_df = 1; txclk_df <= 128; txclk_df++) {
			rate_ideal = rate[index] * txclk_df * 64ULL;
			if (round)
				rate_actual = clk_round_rate(clk, rate_ideal);
			else
				rate_actual = clk_get_rate(clk);

			arate = rate_actual / 64;
			arate /= txclk_df * sysclk_df;

			if (arate == rate[index]) {
				/* We are lucky */
				savesub = 0;
				spdif_priv->txclk_df[index] = txclk_df;
				spdif_priv->sysclk_df[index] = sysclk_df;
				spdif_priv->txrate[index] = arate;
				goto out;
			} else if (arate / rate[index] == 1) {
				/* A little bigger than expect */
				sub = (u64)(arate - rate[index]) * 100000;
				do_div(sub, rate[index]);
				if (sub >= savesub)
					continue;
				savesub = sub;
				spdif_priv->txclk_df[index] = txclk_df;
				spdif_priv->sysclk_df[index] = sysclk_df;
				spdif_priv->txrate[index] = arate;
			} else if (rate[index] / arate == 1) {
				/* A little smaller than expect */
				sub = (u64)(rate[index] - arate) * 100000;
				do_div(sub, rate[index]);
				if (sub >= savesub)
					continue;
				savesub = sub;
				spdif_priv->txclk_df[index] = txclk_df;
				spdif_priv->sysclk_df[index] = sysclk_df;
				spdif_priv->txrate[index] = arate;
			}
		}
	}

out:
	return savesub;
}