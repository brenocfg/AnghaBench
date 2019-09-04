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
struct TYPE_2__ {int (* get_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum s3fwrn5_mode s3fwrn5_get_mode(struct s3fwrn5_info *info)
{
	if (!info->phy_ops->get_mode)
		return -ENOTSUPP;

	return info->phy_ops->get_mode(info->phy_id);
}