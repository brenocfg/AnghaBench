#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* host_if; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_6__ {TYPE_1__* host_global_regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  haint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t dwc_otg_read_host_all_channels_intr(dwc_otg_core_if_t *
							   _core_if)
{
	return (DWC_READ_REG32(&_core_if->host_if->host_global_regs->haint));
}