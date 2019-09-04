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
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int hi3660_reset_assert (struct reset_controller_dev*,unsigned long) ; 
 int hi3660_reset_deassert (struct reset_controller_dev*,unsigned long) ; 

__attribute__((used)) static int hi3660_reset_dev(struct reset_controller_dev *rcdev,
			    unsigned long idx)
{
	int err;

	err = hi3660_reset_assert(rcdev, idx);
	if (err)
		return err;

	return hi3660_reset_deassert(rcdev, idx);
}