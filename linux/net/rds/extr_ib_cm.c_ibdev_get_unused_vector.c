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
struct rds_ib_device {int* vector_load; TYPE_1__* dev; } ;
struct TYPE_2__ {int num_comp_vectors; } ;

/* Variables and functions */

__attribute__((used)) static inline int ibdev_get_unused_vector(struct rds_ib_device *rds_ibdev)
{
	int min = rds_ibdev->vector_load[rds_ibdev->dev->num_comp_vectors - 1];
	int index = rds_ibdev->dev->num_comp_vectors - 1;
	int i;

	for (i = rds_ibdev->dev->num_comp_vectors - 1; i >= 0; i--) {
		if (rds_ibdev->vector_load[i] < min) {
			index = i;
			min = rds_ibdev->vector_load[i];
		}
	}

	rds_ibdev->vector_load[index]++;
	return index;
}