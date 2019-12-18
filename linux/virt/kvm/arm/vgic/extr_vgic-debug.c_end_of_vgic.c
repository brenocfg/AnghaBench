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
struct vgic_state_iter {scalar_t__ dist_id; scalar_t__ vcpu_id; scalar_t__ nr_cpus; scalar_t__ intid; scalar_t__ nr_spis; scalar_t__ lpi_idx; scalar_t__ nr_lpis; } ;

/* Variables and functions */
 scalar_t__ VGIC_NR_PRIVATE_IRQS ; 

__attribute__((used)) static bool end_of_vgic(struct vgic_state_iter *iter)
{
	return iter->dist_id > 0 &&
		iter->vcpu_id == iter->nr_cpus &&
		iter->intid >= (iter->nr_spis + VGIC_NR_PRIVATE_IRQS) &&
		iter->lpi_idx > iter->nr_lpis;
}