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
struct es7241_clock_mode {int slv_mfs_num; unsigned int* slv_mfs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  es7241_set_mode (struct es7241_data*,int,int) ; 

__attribute__((used)) static int es7241_set_slave_mode(struct es7241_data *priv,
				 const struct es7241_clock_mode *mode,
				 unsigned int mfs)
{
	int j;

	if (!mfs)
		goto out_ok;

	for (j = 0; j < mode->slv_mfs_num; j++) {
		if (mode->slv_mfs[j] == mfs)
			goto out_ok;
	}

	return -EINVAL;

out_ok:
	es7241_set_mode(priv, 1, 1);
	return 0;
}