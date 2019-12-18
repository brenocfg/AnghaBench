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
struct TYPE_2__ {int nr_lr; } ;

/* Variables and functions */
 TYPE_1__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  vgic_v2_write_lr (int,int /*<<< orphan*/ ) ; 

void vgic_v2_init_lrs(void)
{
	int i;

	for (i = 0; i < kvm_vgic_global_state.nr_lr; i++)
		vgic_v2_write_lr(i, 0);
}