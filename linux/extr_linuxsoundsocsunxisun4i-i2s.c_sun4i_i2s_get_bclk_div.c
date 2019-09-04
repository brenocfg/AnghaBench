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
 struct sun4i_i2s_clk_div* sun4i_i2s_bclk_div ; 

__attribute__((used)) static int sun4i_i2s_get_bclk_div(struct sun4i_i2s *i2s,
				  unsigned int oversample_rate,
				  unsigned int word_size)
{
	int div = oversample_rate / word_size / 2;
	int i;

	for (i = 0; i < ARRAY_SIZE(sun4i_i2s_bclk_div); i++) {
		const struct sun4i_i2s_clk_div *bdiv = &sun4i_i2s_bclk_div[i];

		if (bdiv->div == div)
			return bdiv->val;
	}

	return -EINVAL;
}