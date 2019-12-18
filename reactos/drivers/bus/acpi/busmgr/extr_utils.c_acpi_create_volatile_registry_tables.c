#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int UINT32 ;
struct TYPE_7__ {int Revision; scalar_t__ RsdtPhysicalAddress; scalar_t__ XsdtPhysicalAddress; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_1__ ACPI_TABLE_RSDP ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_RSDT_ENTRY_SIZE ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 int /*<<< orphan*/  ACPI_SIG_FADT ; 
 int ACPI_XSDT_ENTRY_SIZE ; 
 int /*<<< orphan*/  AcpiGbl_DoNotUseXsdt ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ AcpiOsGetRootPointer () ; 
 TYPE_1__* AcpiOsMapMemory (scalar_t__,int) ; 
 int /*<<< orphan*/  AcpiOsUnmapMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int OBJ_CASE_INSENSITIVE ; 
 int OBJ_KERNEL_HANDLE ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZwCreateKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_create_registry_table (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 

NTSTATUS
acpi_create_volatile_registry_tables(void)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING HardwareKeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\HARDWARE\\ACPI");
    HANDLE KeyHandle = NULL;
    NTSTATUS Status;
    ACPI_STATUS AcpiStatus;
    ACPI_TABLE_HEADER *OutTable;
    ACPI_PHYSICAL_ADDRESS RsdpAddress;
    ACPI_TABLE_RSDP *Rsdp;
    ACPI_PHYSICAL_ADDRESS Address;
    UINT32 TableEntrySize;

    /* Create Main Hardware ACPI key*/
    InitializeObjectAttributes(&ObjectAttributes,
                               &HardwareKeyName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    Status = ZwCreateKey(&KeyHandle,
                         KEY_WRITE,
                         &ObjectAttributes,
                         0,
                         NULL,
                         REG_OPTION_VOLATILE,
                         NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwCreateKey() for ACPI failed (Status 0x%08lx)\n", Status);
        return Status;
    }
    /* Read DSDT table */
    AcpiStatus = AcpiGetTable(ACPI_SIG_DSDT, 0, &OutTable);
    if (ACPI_FAILURE(AcpiStatus))
    {
        DPRINT1("AcpiGetTable() for DSDT failed (Status 0x%08lx)\n", AcpiStatus);
        Status = STATUS_UNSUCCESSFUL;
        goto done;
    }
    /* Dump DSDT table */
    Status = acpi_create_registry_table(KeyHandle, OutTable, L"DSDT");
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("acpi_dump_table_to_registry() for DSDT failed (Status 0x%08lx)\n", Status);
        goto done;
    }
    /* Read FACS table */
    AcpiStatus = AcpiGetTable(ACPI_SIG_FACS, 0, &OutTable);
    if (ACPI_FAILURE(AcpiStatus))
    {
        DPRINT1("AcpiGetTable() for FACS failed (Status 0x%08lx)\n", AcpiStatus);
        Status = STATUS_UNSUCCESSFUL;
        goto done;
    }
    /* Dump FACS table */
    Status = acpi_create_registry_table(KeyHandle, OutTable, L"FACS");
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("acpi_dump_table_to_registry() for FACS failed (Status 0x%08lx)\n", Status);
        goto done;
    }
    /* Read FACS table */
    AcpiStatus = AcpiGetTable(ACPI_SIG_FADT, 0, &OutTable);
    if (ACPI_FAILURE(AcpiStatus))
    {
        DPRINT1("AcpiGetTable() for FADT failed (Status 0x%08lx)\n", AcpiStatus);
        Status = STATUS_UNSUCCESSFUL;
        goto done;
    }
    /* Dump FADT table */
    Status = acpi_create_registry_table(KeyHandle, OutTable, L"FADT");
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("acpi_dump_table_to_registry() for FADT failed (Status 0x%08lx)\n", Status);
        goto done;
    }
    /* This is a rough copy from ACPICA reading of RSDT/XSDT and added to avoid patching acpica */
    RsdpAddress = AcpiOsGetRootPointer();
    /* Map the entire RSDP and extract the address of the RSDT or XSDT */
    Rsdp = AcpiOsMapMemory(RsdpAddress, sizeof(ACPI_TABLE_RSDP));
    if (!Rsdp)
    {
        DPRINT1("AcpiOsMapMemory() failed\n");
        Status = STATUS_NO_MEMORY;
        goto done;
    }
    /* Use XSDT if present and not overridden. Otherwise, use RSDT */
    if ((Rsdp->Revision > 1) &&
        Rsdp->XsdtPhysicalAddress &&
        !AcpiGbl_DoNotUseXsdt)
    {
        /*
        * RSDP contains an XSDT (64-bit physical addresses). We must use
        * the XSDT if the revision is > 1 and the XSDT pointer is present,
        * as per the ACPI specification.
        */
        Address = (ACPI_PHYSICAL_ADDRESS)Rsdp->XsdtPhysicalAddress;
        TableEntrySize = ACPI_XSDT_ENTRY_SIZE;
    }
    else
    {
        /* Root table is an RSDT (32-bit physical addresses) */
        Address = (ACPI_PHYSICAL_ADDRESS)Rsdp->RsdtPhysicalAddress;
        TableEntrySize = ACPI_RSDT_ENTRY_SIZE;
    }
    /*
    * It is not possible to map more than one entry in some environments,
    * so unmap the RSDP here before mapping other tables
    */
    AcpiOsUnmapMemory(Rsdp, sizeof(ACPI_TABLE_RSDP));
    OutTable = AcpiOsMapMemory(Address, TableEntrySize);
    if (!OutTable)
    {
        DPRINT1("AcpiOsMapMemory() failed\n");
        Status = STATUS_NO_MEMORY;
        goto done;
    }
    /* Dump RSDT table */
    Status = acpi_create_registry_table(KeyHandle, OutTable, L"RSDT");
    AcpiOsUnmapMemory(OutTable, TableEntrySize);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("acpi_dump_table_to_registry() for RSDT failed (Status 0x%08lx)\n", Status);
    }

done:
    ZwClose(KeyHandle);
    return Status;
}