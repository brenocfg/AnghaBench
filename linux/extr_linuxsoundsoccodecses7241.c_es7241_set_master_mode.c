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
struct es7241_data {int dummy; } ;
struct es7241_clock_mode {unsigned int mst_mfs; int /*<<< orphan*/  mst_m1; int /*<<< orphan*/  mst_m0; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  es7241_set_mode (struct es7241_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int es7241_set_master_mode(struct es7241_data *priv,
				  const struct es7241_clock_mode *mode,
				  unsigned int mfs)
{
	/*
	 * We can't really set clock ratio, if the mclk/lrclk is different
	 * from what we provide, then error out
	 */
	if (mfs && mfs != mode->mst_mfs)
		return -EINVAL;

	es7241_set_mode(priv, mode->mst_m0, mode->mst_m1);

	return 0;
}