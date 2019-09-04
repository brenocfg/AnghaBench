#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  prtpwr; } ;
struct TYPE_8__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_3__ hprt0_data_t ;
struct TYPE_9__ {TYPE_1__* host_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_6__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ ) ; 

uint32_t dwc_otg_get_prtpower(dwc_otg_core_if_t * core_if)
{
	hprt0_data_t hprt0;
	hprt0.d32 = DWC_READ_REG32(core_if->host_if->hprt0);
	return hprt0.b.prtpwr;

}