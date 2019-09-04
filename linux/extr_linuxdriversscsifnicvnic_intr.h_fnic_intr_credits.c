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
struct vnic_intr {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_credits; } ;

/* Variables and functions */
 unsigned int ioread32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int vnic_intr_credits(struct vnic_intr *intr)
{
	return ioread32(&intr->ctrl->int_credits);
}