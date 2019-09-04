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
struct ctlr_info {int /*<<< orphan*/  scsi_host; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int scsi_add_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_scan_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_scsi_add_host(struct ctlr_info *h)
{
	int rv;

	rv = scsi_add_host(h->scsi_host, &h->pdev->dev);
	if (rv) {
		dev_err(&h->pdev->dev, "scsi_add_host failed\n");
		return rv;
	}
	scsi_scan_host(h->scsi_host);
	return 0;
}