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
struct TYPE_2__ {scalar_t__ state; } ;
struct lpfc_hba {TYPE_1__ mbox_ext_buf_ctx; } ;

/* Variables and functions */
 scalar_t__ LPFC_BSG_MBOX_ABTS ; 
 scalar_t__ LPFC_BSG_MBOX_PORT ; 
 int /*<<< orphan*/  lpfc_bsg_mbox_ext_session_reset (struct lpfc_hba*) ; 

__attribute__((used)) static void
lpfc_bsg_mbox_ext_abort(struct lpfc_hba *phba)
{
	if (phba->mbox_ext_buf_ctx.state == LPFC_BSG_MBOX_PORT)
		phba->mbox_ext_buf_ctx.state = LPFC_BSG_MBOX_ABTS;
	else
		lpfc_bsg_mbox_ext_session_reset(phba);
	return;
}