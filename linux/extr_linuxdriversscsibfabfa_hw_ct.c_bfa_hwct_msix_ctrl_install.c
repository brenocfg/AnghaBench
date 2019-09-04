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
struct TYPE_2__ {int nvecs; int /*<<< orphan*/ * handler; } ;
struct bfa_s {TYPE_1__ msix; } ;

/* Variables and functions */
 size_t BFI_MSIX_LPU_ERR_CT ; 
 int /*<<< orphan*/  bfa_msix_all ; 
 int /*<<< orphan*/  bfa_msix_lpu_err ; 

void
bfa_hwct_msix_ctrl_install(struct bfa_s *bfa)
{
	if (bfa->msix.nvecs == 0)
		return;

	if (bfa->msix.nvecs == 1)
		bfa->msix.handler[BFI_MSIX_LPU_ERR_CT] = bfa_msix_all;
	else
		bfa->msix.handler[BFI_MSIX_LPU_ERR_CT] = bfa_msix_lpu_err;
}