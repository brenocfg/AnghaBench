#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  AslCompilerId; int /*<<< orphan*/  OemTableId; int /*<<< orphan*/  OemId; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_TABLE_ID_SIZE ; 
 int /*<<< orphan*/  AcpiTbFixString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
AcpiTbCleanupTableHeader (
    ACPI_TABLE_HEADER       *OutHeader,
    ACPI_TABLE_HEADER       *Header)
{

    memcpy (OutHeader, Header, sizeof (ACPI_TABLE_HEADER));

    AcpiTbFixString (OutHeader->Signature, ACPI_NAMESEG_SIZE);
    AcpiTbFixString (OutHeader->OemId, ACPI_OEM_ID_SIZE);
    AcpiTbFixString (OutHeader->OemTableId, ACPI_OEM_TABLE_ID_SIZE);
    AcpiTbFixString (OutHeader->AslCompilerId, ACPI_NAMESEG_SIZE);
}