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
struct hisi_sas_device {int /*<<< orphan*/  sata_idx; int /*<<< orphan*/  sas_device; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {int /*<<< orphan*/  sata_dev_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_sata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_device_v2_hw(struct hisi_sas_device *sas_dev)
{
	struct hisi_hba *hisi_hba = sas_dev->hisi_hba;

	/* SoC bug workaround */
	if (dev_is_sata(sas_dev->sas_device))
		clear_bit(sas_dev->sata_idx, hisi_hba->sata_dev_bitmap);
}