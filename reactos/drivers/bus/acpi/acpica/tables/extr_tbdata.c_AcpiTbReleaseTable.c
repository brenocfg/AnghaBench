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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
#define  ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL 130 
#define  ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL 129 
#define  ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL 128 
 int ACPI_TABLE_ORIGIN_MASK ; 
 int /*<<< orphan*/  AcpiOsUnmapMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
AcpiTbReleaseTable (
    ACPI_TABLE_HEADER       *Table,
    UINT32                  TableLength,
    UINT8                   TableFlags)
{

    switch (TableFlags & ACPI_TABLE_ORIGIN_MASK)
    {
    case ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

        AcpiOsUnmapMemory (Table, TableLength);
        break;

    case ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:
    case ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:
    default:

        break;
    }
}