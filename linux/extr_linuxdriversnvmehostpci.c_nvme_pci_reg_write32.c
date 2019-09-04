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
typedef  scalar_t__ u32 ;
struct nvme_ctrl {int dummy; } ;
struct TYPE_2__ {scalar_t__ bar; } ;

/* Variables and functions */
 TYPE_1__* to_nvme_dev (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nvme_pci_reg_write32(struct nvme_ctrl *ctrl, u32 off, u32 val)
{
	writel(val, to_nvme_dev(ctrl)->bar + off);
	return 0;
}