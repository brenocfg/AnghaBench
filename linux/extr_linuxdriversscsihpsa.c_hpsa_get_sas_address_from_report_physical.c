#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ctlr_info {TYPE_1__* pdev; } ;
struct ReportExtendedLUNdata {TYPE_2__* LUN; int /*<<< orphan*/  LUNListLength; } ;
struct TYPE_4__ {int /*<<< orphan*/ * wwid; int /*<<< orphan*/ * lunid; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 scalar_t__ hpsa_scsi_do_report_phys_luns (struct ctlr_info*,struct ReportExtendedLUNdata*,int) ; 
 int /*<<< orphan*/  kfree (struct ReportExtendedLUNdata*) ; 
 struct ReportExtendedLUNdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static u64 hpsa_get_sas_address_from_report_physical(struct ctlr_info *h,
						unsigned char *scsi3addr)
{
	struct ReportExtendedLUNdata *physdev;
	u32 nphysicals;
	u64 sa = 0;
	int i;

	physdev = kzalloc(sizeof(*physdev), GFP_KERNEL);
	if (!physdev)
		return 0;

	if (hpsa_scsi_do_report_phys_luns(h, physdev, sizeof(*physdev))) {
		dev_err(&h->pdev->dev, "report physical LUNs failed.\n");
		kfree(physdev);
		return 0;
	}
	nphysicals = get_unaligned_be32(physdev->LUNListLength) / 24;

	for (i = 0; i < nphysicals; i++)
		if (!memcmp(&physdev->LUN[i].lunid[0], scsi3addr, 8)) {
			sa = get_unaligned_be64(&physdev->LUN[i].wwid[0]);
			break;
		}

	kfree(physdev);

	return sa;
}