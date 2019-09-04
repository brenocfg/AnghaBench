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
typedef  int /*<<< orphan*/  u32 ;
struct vme_bridge {int /*<<< orphan*/  parent; struct ca91cx42_driver* driver_priv; } ;
struct ca91cx42_driver {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA91CX42_LINT_VERR ; 
 scalar_t__ DGCS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static u32 ca91cx42_VERR_irqhandler(struct vme_bridge *ca91cx42_bridge)
{
	int val;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	val = ioread32(bridge->base + DGCS);

	if (!(val & 0x00000800)) {
		dev_err(ca91cx42_bridge->parent, "ca91cx42_VERR_irqhandler DMA "
			"Read Error DGCS=%08X\n", val);
	}

	return CA91CX42_LINT_VERR;
}