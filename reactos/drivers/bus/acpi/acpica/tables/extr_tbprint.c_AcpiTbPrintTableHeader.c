#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ Revision; int Length; int /*<<< orphan*/  OemId; } ;
struct TYPE_7__ {int /*<<< orphan*/  AslCompilerRevision; int /*<<< orphan*/  AslCompilerId; int /*<<< orphan*/  OemRevision; int /*<<< orphan*/  OemTableId; int /*<<< orphan*/  OemId; int /*<<< orphan*/  Revision; int /*<<< orphan*/  Length; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 TYPE_5__* ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 int /*<<< orphan*/  ACPI_TABLE_RSDP ; 
 scalar_t__ ACPI_VALIDATE_RSDP_SIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbCleanupTableHeader (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiTbFixString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AcpiTbPrintTableHeader (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       *Header)
{
    ACPI_TABLE_HEADER       LocalHeader;


    if (ACPI_COMPARE_NAMESEG (Header->Signature, ACPI_SIG_FACS))
    {
        /* FACS only has signature and length fields */

        ACPI_INFO (("%-4.4s 0x%8.8X%8.8X %06X",
            Header->Signature, ACPI_FORMAT_UINT64 (Address),
            Header->Length));
    }
    else if (ACPI_VALIDATE_RSDP_SIG (Header->Signature))
    {
        /* RSDP has no common fields */

        memcpy (LocalHeader.OemId, ACPI_CAST_PTR (ACPI_TABLE_RSDP,
            Header)->OemId, ACPI_OEM_ID_SIZE);
        AcpiTbFixString (LocalHeader.OemId, ACPI_OEM_ID_SIZE);

        ACPI_INFO (("RSDP 0x%8.8X%8.8X %06X (v%.2d %-6.6s)",
            ACPI_FORMAT_UINT64 (Address),
            (ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->Revision > 0) ?
                ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->Length : 20,
            ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->Revision,
            LocalHeader.OemId));
    }
    else
    {
        /* Standard ACPI table with full common header */

        AcpiTbCleanupTableHeader (&LocalHeader, Header);

        ACPI_INFO ((
            "%-4.4s 0x%8.8X%8.8X"
            " %06X (v%.2d %-6.6s %-8.8s %08X %-4.4s %08X)",
            LocalHeader.Signature, ACPI_FORMAT_UINT64 (Address),
            LocalHeader.Length, LocalHeader.Revision, LocalHeader.OemId,
            LocalHeader.OemTableId, LocalHeader.OemRevision,
            LocalHeader.AslCompilerId, LocalHeader.AslCompilerRevision));
    }
}