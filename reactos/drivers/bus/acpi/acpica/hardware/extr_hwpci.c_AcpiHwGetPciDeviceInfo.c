#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  void* UINT16 ;
struct TYPE_4__ {void* Bus; int /*<<< orphan*/  Function; int /*<<< orphan*/  Device; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_PCI_ID ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_LODWORD (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetType (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  AcpiOsReadPciConfiguration (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  AcpiUtEvaluateNumericObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  METHOD_NAME__ADR ; 
 int /*<<< orphan*/  PCI_CFG_HEADER_TYPE_REG ; 
 int /*<<< orphan*/  PCI_CFG_PRIMARY_BUS_NUMBER_REG ; 
 int /*<<< orphan*/  PCI_CFG_SECONDARY_BUS_NUMBER_REG ; 
 scalar_t__ PCI_HEADER_TYPE_MASK ; 
 scalar_t__ PCI_TYPE_BRIDGE ; 
 scalar_t__ PCI_TYPE_CARDBUS_BRIDGE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static ACPI_STATUS
AcpiHwGetPciDeviceInfo (
    ACPI_PCI_ID             *PciId,
    ACPI_HANDLE             PciDevice,
    UINT16                  *BusNumber,
    BOOLEAN                 *IsBridge)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_TYPE        ObjectType;
    UINT64                  ReturnValue;
    UINT64                  PciValue;


    /* We only care about objects of type Device */

    Status = AcpiGetType (PciDevice, &ObjectType);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    if (ObjectType != ACPI_TYPE_DEVICE)
    {
        return (AE_OK);
    }

    /* We need an _ADR. Ignore device if not present */

    Status = AcpiUtEvaluateNumericObject (METHOD_NAME__ADR,
        PciDevice, &ReturnValue);
    if (ACPI_FAILURE (Status))
    {
        return (AE_OK);
    }

    /*
     * From _ADR, get the PCI Device and Function and
     * update the PCI ID.
     */
    PciId->Device = ACPI_HIWORD (ACPI_LODWORD (ReturnValue));
    PciId->Function = ACPI_LOWORD (ACPI_LODWORD (ReturnValue));

    /*
     * If the previous device was a bridge, use the previous
     * device bus number
     */
    if (*IsBridge)
    {
        PciId->Bus = *BusNumber;
    }

    /*
     * Get the bus numbers from PCI Config space:
     *
     * First, get the PCI HeaderType
     */
    *IsBridge = FALSE;
    Status = AcpiOsReadPciConfiguration (PciId,
        PCI_CFG_HEADER_TYPE_REG, &PciValue, 8);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* We only care about bridges (1=PciBridge, 2=CardBusBridge) */

    PciValue &= PCI_HEADER_TYPE_MASK;

    if ((PciValue != PCI_TYPE_BRIDGE) &&
        (PciValue != PCI_TYPE_CARDBUS_BRIDGE))
    {
        return (AE_OK);
    }

    /* Bridge: Get the Primary BusNumber */

    Status = AcpiOsReadPciConfiguration (PciId,
        PCI_CFG_PRIMARY_BUS_NUMBER_REG, &PciValue, 8);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    *IsBridge = TRUE;
    PciId->Bus = (UINT16) PciValue;

    /* Bridge: Get the Secondary BusNumber */

    Status = AcpiOsReadPciConfiguration (PciId,
        PCI_CFG_SECONDARY_BUS_NUMBER_REG, &PciValue, 8);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    *BusNumber = (UINT16) PciValue;
    return (AE_OK);
}