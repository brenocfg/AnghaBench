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
struct hisi_hba {int /*<<< orphan*/  sata_dev_bitmap; } ;

/* Variables and functions */
 int hw_init_v2_hw (struct hisi_hba*) ; 
 int interrupt_init_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hisi_sas_v2_init(struct hisi_hba *hisi_hba)
{
	int rc;

	memset(hisi_hba->sata_dev_bitmap, 0, sizeof(hisi_hba->sata_dev_bitmap));

	rc = hw_init_v2_hw(hisi_hba);
	if (rc)
		return rc;

	rc = interrupt_init_v2_hw(hisi_hba);
	if (rc)
		return rc;

	return 0;
}