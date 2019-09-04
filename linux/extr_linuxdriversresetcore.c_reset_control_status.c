#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reset_control {int /*<<< orphan*/  id; TYPE_2__* rcdev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* status ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  IS_ERR (struct reset_control*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ reset_control_is_array (struct reset_control*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int reset_control_status(struct reset_control *rstc)
{
	if (!rstc)
		return 0;

	if (WARN_ON(IS_ERR(rstc)) || reset_control_is_array(rstc))
		return -EINVAL;

	if (rstc->rcdev->ops->status)
		return rstc->rcdev->ops->status(rstc->rcdev, rstc->id);

	return -ENOTSUPP;
}