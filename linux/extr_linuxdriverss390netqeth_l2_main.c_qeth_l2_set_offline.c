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
struct ccwgroup_device {int dummy; } ;

/* Variables and functions */
 int __qeth_l2_set_offline (struct ccwgroup_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_set_offline(struct ccwgroup_device *cgdev)
{
	return __qeth_l2_set_offline(cgdev, 0);
}