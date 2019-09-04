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
typedef  int u32 ;

/* Variables and functions */
 int MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE ; 
 int MPI26_PCIE_DEVINFO_NVME ; 

__attribute__((used)) static int
_scsih_is_nvme_device(u32 device_info)
{
	if ((device_info & MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE)
					== MPI26_PCIE_DEVINFO_NVME)
		return 1;
	else
		return 0;
}