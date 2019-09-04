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
struct se_hba {struct rd_host* hba_ptr; int /*<<< orphan*/  hba_id; } ;
struct rd_host {int /*<<< orphan*/  rd_host_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rd_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rd_detach_hba(struct se_hba *hba)
{
	struct rd_host *rd_host = hba->hba_ptr;

	pr_debug("CORE_HBA[%d] - Detached Ramdisk HBA: %u from"
		" Generic Target Core\n", hba->hba_id, rd_host->rd_host_id);

	kfree(rd_host);
	hba->hba_ptr = NULL;
}