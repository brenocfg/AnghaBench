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
struct snic {int /*<<< orphan*/  shost; int /*<<< orphan*/  vdev; } ;
typedef  enum vnic_dev_intr_mode { ____Placeholder_vnic_dev_intr_mode } vnic_dev_intr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SNIC_MSIX_ERR_NOTIFY ; 
 int VNIC_DEV_INTR_MODE_MSIX ; 
 int svnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int svnic_dev_notify_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snic_notify_set(struct snic *snic)
{
	int ret = 0;
	enum vnic_dev_intr_mode intr_mode;

	intr_mode = svnic_dev_get_intr_mode(snic->vdev);

	if (intr_mode == VNIC_DEV_INTR_MODE_MSIX) {
		ret = svnic_dev_notify_set(snic->vdev, SNIC_MSIX_ERR_NOTIFY);
	} else {
		SNIC_HOST_ERR(snic->shost,
			      "Interrupt mode should be setup before devcmd notify set %d\n",
			      intr_mode);
		ret = -1;
	}

	return ret;
}