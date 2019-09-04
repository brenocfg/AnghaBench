#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_ntb_vec {int /*<<< orphan*/  num; TYPE_3__* ndev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_6__ {TYPE_2__ ntb; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndev_interrupt (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ndev_vec_isr(int irq, void *dev)
{
	struct intel_ntb_vec *nvec = dev;

	dev_dbg(&nvec->ndev->ntb.pdev->dev, "irq: %d  nvec->num: %d\n",
		irq, nvec->num);

	return ndev_interrupt(nvec->ndev, nvec->num);
}