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
struct sun4i_i2s_clk_div {int div; int val; } ;
struct sun4i_i2s {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sun4i_i2s_clk_div*) ; 
 int EINVAL ; 
 struct sun4i_i2s_clk_div* sun4i_i2s_mclk_div ; 

__attribute__((used)) static int sun4i_i2s_get_mclk_div(struct sun4i_i2s *i2s,
				  unsigned int oversample_rate,
				  unsigned int module_rate,
				  unsigned int sampling_rate)
{
	int div = module_rate / sampling_rate / oversample_rate;
	int i;

	for (i = 0; i < ARRAY_SIZE(sun4i_i2s_mclk_div); i++) {
		const struct sun4i_i2s_clk_div *mdiv = &sun4i_i2s_mclk_div[i];

		if (mdiv->div == div)
			return mdiv->val;
	}

	return -EINVAL;
}