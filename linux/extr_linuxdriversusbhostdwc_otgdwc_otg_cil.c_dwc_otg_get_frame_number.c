#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_2__* dev_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int /*<<< orphan*/  soffn; } ;
struct TYPE_11__ {TYPE_3__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_5__ dsts_data_t ;
struct TYPE_8__ {TYPE_1__* dev_global_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  dsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

uint32_t dwc_otg_get_frame_number(dwc_otg_core_if_t * core_if)
{
	dsts_data_t dsts;
	dsts.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dsts);

	/* read current frame/microframe number from DSTS register */
	return dsts.b.soffn;
}