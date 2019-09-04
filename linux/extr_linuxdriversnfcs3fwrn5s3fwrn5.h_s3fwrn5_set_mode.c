#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s3fwrn5_info {int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
typedef  enum s3fwrn5_mode { ____Placeholder_s3fwrn5_mode } s3fwrn5_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mode ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int s3fwrn5_set_mode(struct s3fwrn5_info *info,
	enum s3fwrn5_mode mode)
{
	if (!info->phy_ops->set_mode)
		return -ENOTSUPP;

	info->phy_ops->set_mode(info->phy_id, mode);

	return 0;
}