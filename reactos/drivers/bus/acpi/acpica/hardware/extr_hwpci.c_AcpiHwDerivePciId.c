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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PCI_ID ;
typedef  int /*<<< orphan*/  ACPI_PCI_DEVICE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AcpiHwBuildPciList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiHwDeletePciList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiHwProcessPciList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HwDerivePciId ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwDerivePciId (
    ACPI_PCI_ID             *PciId,
    ACPI_HANDLE             RootPciDevice,
    ACPI_HANDLE             PciRegion)
{
    ACPI_STATUS             Status;
    ACPI_PCI_DEVICE         *ListHead;


    ACPI_FUNCTION_TRACE (HwDerivePciId);


    if (!PciId)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Build a list of PCI devices, from PciRegion up to RootPciDevice */

    Status = AcpiHwBuildPciList (RootPciDevice, PciRegion, &ListHead);
    if (ACPI_SUCCESS (Status))
    {
        /* Walk the list, updating the PCI device/function/bus numbers */

        Status = AcpiHwProcessPciList (PciId, ListHead);

        /* Delete the list */

        AcpiHwDeletePciList (ListHead);
    }

    return_ACPI_STATUS (Status);
}