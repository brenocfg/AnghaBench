#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_8__ {int /*<<< orphan*/  Pointer; TYPE_7__ Signature; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int /*<<< orphan*/  ACPI_MTX_TABLES ; 
 int /*<<< orphan*/  ACPI_SIG_SSDT ; 
 int /*<<< orphan*/  ACPI_TABLE_EVENT_INSTALL ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiGbl_DisableSsdtTableInstall ; 
 scalar_t__ AcpiTbAcquireTempTable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbInstallTableWithOverride (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbNotifyTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbReleaseTempTable (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiTbUninstallTable (TYPE_1__*) ; 
 scalar_t__ AcpiTbVerifyTempTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TbInstallStandardTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiTbInstallStandardTable (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT8                   Flags,
    BOOLEAN                 Reload,
    BOOLEAN                 Override,
    UINT32                  *TableIndex)
{
    UINT32                  i;
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_DESC         NewTableDesc;


    ACPI_FUNCTION_TRACE (TbInstallStandardTable);


    /* Acquire a temporary table descriptor for validation */

    Status = AcpiTbAcquireTempTable (&NewTableDesc, Address, Flags);
    if (ACPI_FAILURE (Status))
    {
        ACPI_ERROR ((AE_INFO,
            "Could not acquire table length at %8.8X%8.8X",
            ACPI_FORMAT_UINT64 (Address)));
        return_ACPI_STATUS (Status);
    }

    /*
     * Optionally do not load any SSDTs from the RSDT/XSDT. This can
     * be useful for debugging ACPI problems on some machines.
     */
    if (!Reload &&
        AcpiGbl_DisableSsdtTableInstall &&
        ACPI_COMPARE_NAMESEG (&NewTableDesc.Signature, ACPI_SIG_SSDT))
    {
        ACPI_INFO ((
            "Ignoring installation of %4.4s at %8.8X%8.8X",
            NewTableDesc.Signature.Ascii, ACPI_FORMAT_UINT64 (Address)));
        goto ReleaseAndExit;
    }

    /* Acquire the table lock */

    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);

    /* Validate and verify a table before installation */

    Status = AcpiTbVerifyTempTable (&NewTableDesc, NULL, &i);
    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_CTRL_TERMINATE)
        {
            /*
             * Table was unloaded, allow it to be reloaded.
             * As we are going to return AE_OK to the caller, we should
             * take the responsibility of freeing the input descriptor.
             * Refill the input descriptor to ensure
             * AcpiTbInstallTableWithOverride() can be called again to
             * indicate the re-installation.
             */
            AcpiTbUninstallTable (&NewTableDesc);
            (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
            *TableIndex = i;
            return_ACPI_STATUS (AE_OK);
        }
        goto UnlockAndExit;
    }

    /* Add the table to the global root table list */

    AcpiTbInstallTableWithOverride (&NewTableDesc, Override, TableIndex);

    /* Invoke table handler */

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
    AcpiTbNotifyTable (ACPI_TABLE_EVENT_INSTALL, NewTableDesc.Pointer);
    (void) AcpiUtAcquireMutex (ACPI_MTX_TABLES);

UnlockAndExit:

    /* Release the table lock */

    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);

ReleaseAndExit:

    /* Release the temporary table descriptor */

    AcpiTbReleaseTempTable (&NewTableDesc);
    return_ACPI_STATUS (Status);
}