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
struct ufs_hba {int /*<<< orphan*/  host; int /*<<< orphan*/  scsi_block_reqs_cnt; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_scsi_block_requests(struct ufs_hba *hba)
{
	if (atomic_inc_return(&hba->scsi_block_reqs_cnt) == 1)
		scsi_block_requests(hba->host);
}