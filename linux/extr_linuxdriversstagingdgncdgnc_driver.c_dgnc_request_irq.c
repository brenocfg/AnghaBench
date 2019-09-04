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
struct dgnc_board {int /*<<< orphan*/  state; scalar_t__ irq; TYPE_2__* pdev; TYPE_1__* bd_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_FAILED ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct dgnc_board*) ; 

__attribute__((used)) static int dgnc_request_irq(struct dgnc_board *brd)
{
	if (brd->irq) {
		int rc = request_irq(brd->irq, brd->bd_ops->intr,
				 IRQF_SHARED, "DGNC", brd);
		if (rc) {
			dev_err(&brd->pdev->dev,
				"Failed to hook IRQ %d\n", brd->irq);
			brd->state = BOARD_FAILED;
			return -ENODEV;
		}
	}
	return 0;
}