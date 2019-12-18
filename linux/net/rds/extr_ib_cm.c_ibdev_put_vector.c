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
struct rds_ib_device {int /*<<< orphan*/ * vector_load; } ;

/* Variables and functions */

__attribute__((used)) static inline void ibdev_put_vector(struct rds_ib_device *rds_ibdev, int index)
{
	rds_ibdev->vector_load[index]--;
}