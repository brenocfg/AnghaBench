#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  prtsusp; } ;
struct TYPE_9__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_3__ hprt0_data_t ;
struct TYPE_10__ {TYPE_2__* host_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_read_hprt0 (TYPE_4__*) ; 

void dwc_otg_set_prtsuspend(dwc_otg_core_if_t * core_if, uint32_t val)
{
	hprt0_data_t hprt0;
	hprt0.d32 = dwc_otg_read_hprt0(core_if);
	hprt0.b.prtsusp = val;
	DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
}