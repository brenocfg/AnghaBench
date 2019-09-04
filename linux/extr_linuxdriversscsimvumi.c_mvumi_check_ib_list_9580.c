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
struct mvumi_hba {int max_io; int /*<<< orphan*/  ib_shadow; int /*<<< orphan*/  fw_outstanding; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int mvumi_check_ib_list_9580(struct mvumi_hba *mhba)
{
	unsigned int count;
	if (atomic_read(&mhba->fw_outstanding) >= (mhba->max_io - 1))
		return 0;
	count = ioread32(mhba->ib_shadow);
	if (count == 0xffff)
		return 0;
	return count;
}