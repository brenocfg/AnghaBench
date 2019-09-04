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
struct geni_se {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int geni_se_clk_tbl_get (struct geni_se*,unsigned long**) ; 

int geni_se_clk_freq_match(struct geni_se *se, unsigned long req_freq,
			   unsigned int *index, unsigned long *res_freq,
			   bool exact)
{
	unsigned long *tbl;
	int num_clk_levels;
	int i;

	num_clk_levels = geni_se_clk_tbl_get(se, &tbl);
	if (num_clk_levels < 0)
		return num_clk_levels;

	if (num_clk_levels == 0)
		return -EINVAL;

	*res_freq = 0;
	for (i = 0; i < num_clk_levels; i++) {
		if (!(tbl[i] % req_freq)) {
			*index = i;
			*res_freq = tbl[i];
			return 0;
		}

		if (!(*res_freq) || ((tbl[i] > *res_freq) &&
				     (tbl[i] < req_freq))) {
			*index = i;
			*res_freq = tbl[i];
		}
	}

	if (exact)
		return -EINVAL;

	return 0;
}