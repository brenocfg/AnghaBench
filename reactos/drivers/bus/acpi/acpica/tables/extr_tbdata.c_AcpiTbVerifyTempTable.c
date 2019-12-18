#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {char* Ascii; int /*<<< orphan*/  Integer; } ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Address; TYPE_6__ Signature; int /*<<< orphan*/  Length; int /*<<< orphan*/  Pointer; } ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_IS_VERIFIED ; 
 scalar_t__ AE_BAD_SIGNATURE ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiGbl_EnableTableValidation ; 
 scalar_t__ AcpiTbCheckDuplication (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbInvalidateTable (TYPE_1__*) ; 
 scalar_t__ AcpiTbValidateTempTable (TYPE_1__*) ; 
 scalar_t__ AcpiTbVerifyChecksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiUtValidNameseg (char*) ; 
 int /*<<< orphan*/  TbVerifyTempTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiTbVerifyTempTable (
    ACPI_TABLE_DESC         *TableDesc,
    char                    *Signature,
    UINT32                  *TableIndex)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (TbVerifyTempTable);


    /* Validate the table */

    Status = AcpiTbValidateTempTable (TableDesc);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* If a particular signature is expected (DSDT/FACS), it must match */

    if (Signature &&
        !ACPI_COMPARE_NAMESEG (&TableDesc->Signature, Signature))
    {
        ACPI_BIOS_ERROR ((AE_INFO,
            "Invalid signature 0x%X for ACPI table, expected [%s]",
            TableDesc->Signature.Integer, Signature));
        Status = AE_BAD_SIGNATURE;
        goto InvalidateAndExit;
    }

    if (AcpiGbl_EnableTableValidation)
    {
        /* Verify the checksum */

        Status = AcpiTbVerifyChecksum (TableDesc->Pointer, TableDesc->Length);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, AE_NO_MEMORY,
                "%4.4s 0x%8.8X%8.8X"
                " Attempted table install failed",
                AcpiUtValidNameseg (TableDesc->Signature.Ascii) ?
                    TableDesc->Signature.Ascii : "????",
                ACPI_FORMAT_UINT64 (TableDesc->Address)));

            goto InvalidateAndExit;
        }

        /* Avoid duplications */

        if (TableIndex)
        {
            Status = AcpiTbCheckDuplication (TableDesc, TableIndex);
            if (ACPI_FAILURE (Status))
            {
                if (Status != AE_CTRL_TERMINATE)
                {
                    ACPI_EXCEPTION ((AE_INFO, Status,
                        "%4.4s 0x%8.8X%8.8X"
                        " Table is already loaded",
                        AcpiUtValidNameseg (TableDesc->Signature.Ascii) ?
                            TableDesc->Signature.Ascii : "????",
                        ACPI_FORMAT_UINT64 (TableDesc->Address)));
                }

                goto InvalidateAndExit;
            }
        }

        TableDesc->Flags |= ACPI_TABLE_IS_VERIFIED;
    }

    return_ACPI_STATUS (Status);

InvalidateAndExit:
    AcpiTbInvalidateTable (TableDesc);
    return_ACPI_STATUS (Status);
}