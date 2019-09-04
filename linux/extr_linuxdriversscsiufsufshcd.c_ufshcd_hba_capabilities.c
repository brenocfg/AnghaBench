#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ufs_hba {int capabilities; int nutrs; int nutmrs; } ;

/* Variables and functions */
 int MASK_TASK_MANAGEMENT_REQUEST_SLOTS ; 
 int MASK_TRANSFER_REQUESTS_SLOTS ; 
 int /*<<< orphan*/  REG_CONTROLLER_CAPABILITIES ; 
 int ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ufshcd_hba_capabilities(struct ufs_hba *hba)
{
	hba->capabilities = ufshcd_readl(hba, REG_CONTROLLER_CAPABILITIES);

	/* nutrs and nutmrs are 0 based values */
	hba->nutrs = (hba->capabilities & MASK_TRANSFER_REQUESTS_SLOTS) + 1;
	hba->nutmrs =
	((hba->capabilities & MASK_TASK_MANAGEMENT_REQUEST_SLOTS) >> 16) + 1;
}