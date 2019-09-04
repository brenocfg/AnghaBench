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
struct amd_ntb_dev {int mw_count; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ndev_mw_to_bar(struct amd_ntb_dev *ndev, int idx)
{
	if (idx < 0 || idx > ndev->mw_count)
		return -EINVAL;

	return 1 << idx;
}