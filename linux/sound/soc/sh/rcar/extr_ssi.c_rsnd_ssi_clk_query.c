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
struct rsnd_priv {int dummy; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int rsnd_adg_clk_query (struct rsnd_priv*,unsigned int) ; 
 struct rsnd_priv* rsnd_rdai_to_priv (struct rsnd_dai*) ; 
 int rsnd_rdai_width_get (struct rsnd_dai*) ; 

unsigned int rsnd_ssi_clk_query(struct rsnd_dai *rdai,
		       int param1, int param2, int *idx)
{
	struct rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	int ssi_clk_mul_table[] = {
		1, 2, 4, 8, 16, 6, 12,
	};
	int j, ret;
	unsigned int main_rate;
	int width = rsnd_rdai_width_get(rdai);

	for (j = 0; j < ARRAY_SIZE(ssi_clk_mul_table); j++) {

		/*
		 * It will set SSIWSR.CONT here, but SSICR.CKDV = 000
		 * with it is not allowed. (SSIWSR.WS_MODE with
		 * SSICR.CKDV = 000 is not allowed either).
		 * Skip it. See SSICR.CKDV
		 */
		if (j == 0)
			continue;

		main_rate = width * param1 * param2 * ssi_clk_mul_table[j];

		ret = rsnd_adg_clk_query(priv, main_rate);
		if (ret < 0)
			continue;

		if (idx)
			*idx = j;

		return main_rate;
	}

	return 0;
}