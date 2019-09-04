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
struct scsi_qla_host {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_QLOGIC_ISP8022 ; 
 scalar_t__ PCI_DEVICE_ID_QLOGIC_ISP8042 ; 
 scalar_t__ PCI_DEVICE_ID_QLOGIC_ISP8324 ; 

__attribute__((used)) static inline int is_aer_supported(struct scsi_qla_host *ha)
{
	return ((ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8022) ||
		(ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8324) ||
		(ha->pdev->device == PCI_DEVICE_ID_QLOGIC_ISP8042));
}