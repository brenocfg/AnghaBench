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
struct pci_dev {int dummy; } ;
struct ipr_ioa_cfg {TYPE_2__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ shost_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  __ipr_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  ipr_dump_attr ; 
 int /*<<< orphan*/  ipr_ioa_async_err_log ; 
 int /*<<< orphan*/  ipr_remove_dump_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_remove_trace_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_trace_attr ; 
 struct ipr_ioa_cfg* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_remove_host (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_remove(struct pci_dev *pdev)
{
	struct ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);

	ENTER;

	ipr_remove_trace_file(&ioa_cfg->host->shost_dev.kobj,
			      &ipr_trace_attr);
	ipr_remove_dump_file(&ioa_cfg->host->shost_dev.kobj,
			     &ipr_dump_attr);
	sysfs_remove_bin_file(&ioa_cfg->host->shost_dev.kobj,
			&ipr_ioa_async_err_log);
	scsi_remove_host(ioa_cfg->host);

	__ipr_remove(pdev);

	LEAVE;
}