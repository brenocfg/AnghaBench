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
struct TYPE_7__ {scalar_t__ prtovrcurrchng; scalar_t__ prtenchng; scalar_t__ prtconndet; scalar_t__ prtena; } ;
struct TYPE_8__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_3__ hprt0_data_t ;
struct TYPE_9__ {TYPE_1__* host_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_6__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t dwc_otg_read_hprt0(dwc_otg_core_if_t * _core_if)
{
	hprt0_data_t hprt0;
	hprt0.d32 = DWC_READ_REG32(_core_if->host_if->hprt0);
	hprt0.b.prtena = 0;
	hprt0.b.prtconndet = 0;
	hprt0.b.prtenchng = 0;
	hprt0.b.prtovrcurrchng = 0;
	return hprt0.d32;
}