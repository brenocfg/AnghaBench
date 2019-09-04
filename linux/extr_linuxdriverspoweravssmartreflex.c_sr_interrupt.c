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
typedef  int /*<<< orphan*/  u32 ;
struct omap_sr {int ip_type; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* notify ) (struct omap_sr*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCONFIG_V1 ; 
 int /*<<< orphan*/  IRQSTATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  SR_TYPE_V1 129 
#define  SR_TYPE_V2 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__* sr_class ; 
 int /*<<< orphan*/  sr_read_reg (struct omap_sr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_write_reg (struct omap_sr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_sr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sr_interrupt(int irq, void *data)
{
	struct omap_sr *sr_info = data;
	u32 status = 0;

	switch (sr_info->ip_type) {
	case SR_TYPE_V1:
		/* Read the status bits */
		status = sr_read_reg(sr_info, ERRCONFIG_V1);

		/* Clear them by writing back */
		sr_write_reg(sr_info, ERRCONFIG_V1, status);
		break;
	case SR_TYPE_V2:
		/* Read the status bits */
		status = sr_read_reg(sr_info, IRQSTATUS);

		/* Clear them by writing back */
		sr_write_reg(sr_info, IRQSTATUS, status);
		break;
	default:
		dev_err(&sr_info->pdev->dev, "UNKNOWN IP type %d\n",
			sr_info->ip_type);
		return IRQ_NONE;
	}

	if (sr_class->notify)
		sr_class->notify(sr_info, status);

	return IRQ_HANDLED;
}