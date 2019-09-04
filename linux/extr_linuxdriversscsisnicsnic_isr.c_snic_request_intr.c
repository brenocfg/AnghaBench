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
struct snic {char* name; TYPE_1__* msix; int /*<<< orphan*/  shost; int /*<<< orphan*/  pdev; int /*<<< orphan*/  vdev; } ;
typedef  enum vnic_dev_intr_mode { ____Placeholder_vnic_dev_intr_mode } vnic_dev_intr_mode ;
struct TYPE_2__ {int requested; struct snic* devid; int /*<<< orphan*/  devname; int /*<<< orphan*/  isr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*,int,int) ; 
 size_t SNIC_MSIX_ERR_NOTIFY ; 
 size_t SNIC_MSIX_IO_CMPL ; 
 size_t SNIC_MSIX_WQ ; 
 int VNIC_DEV_INTR_MODE_MSIX ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snic*) ; 
 int /*<<< orphan*/  snic_free_intr (struct snic*) ; 
 int /*<<< orphan*/  snic_isr_msix_err_notify ; 
 int /*<<< orphan*/  snic_isr_msix_io_cmpl ; 
 int /*<<< orphan*/  snic_isr_msix_wq ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int svnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 

int
snic_request_intr(struct snic *snic)
{
	int ret = 0, i;
	enum vnic_dev_intr_mode intr_mode;

	intr_mode = svnic_dev_get_intr_mode(snic->vdev);
	SNIC_BUG_ON(intr_mode != VNIC_DEV_INTR_MODE_MSIX);

	/*
	 * Currently HW supports single WQ and CQ. So passing devid as snic.
	 * When hardware supports multiple WQs and CQs, one idea is
	 * to pass devid as corresponding WQ or CQ ptr and retrieve snic
	 * from queue ptr.
	 * Except for err_notify, which is always one.
	 */
	sprintf(snic->msix[SNIC_MSIX_WQ].devname,
		"%.11s-scsi-wq",
		snic->name);
	snic->msix[SNIC_MSIX_WQ].isr = snic_isr_msix_wq;
	snic->msix[SNIC_MSIX_WQ].devid = snic;

	sprintf(snic->msix[SNIC_MSIX_IO_CMPL].devname,
		"%.11s-io-cmpl",
		snic->name);
	snic->msix[SNIC_MSIX_IO_CMPL].isr = snic_isr_msix_io_cmpl;
	snic->msix[SNIC_MSIX_IO_CMPL].devid = snic;

	sprintf(snic->msix[SNIC_MSIX_ERR_NOTIFY].devname,
		"%.11s-err-notify",
		snic->name);
	snic->msix[SNIC_MSIX_ERR_NOTIFY].isr = snic_isr_msix_err_notify;
	snic->msix[SNIC_MSIX_ERR_NOTIFY].devid = snic;

	for (i = 0; i < ARRAY_SIZE(snic->msix); i++) {
		ret = request_irq(pci_irq_vector(snic->pdev, i),
				  snic->msix[i].isr,
				  0,
				  snic->msix[i].devname,
				  snic->msix[i].devid);
		if (ret) {
			SNIC_HOST_ERR(snic->shost,
				      "MSI-X: request_irq(%d) failed %d\n",
				      i,
				      ret);
			snic_free_intr(snic);
			break;
		}
		snic->msix[i].requested = 1;
	}

	return ret;
}