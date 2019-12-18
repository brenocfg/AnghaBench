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
struct TYPE_6__ {int RuntimeCount; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_GPE_EVENT_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_UINT8_MAX ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvEnableGpe (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiEvUpdateGpeEnableMask (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiHwClearGpe (TYPE_1__*) ; 
 int /*<<< orphan*/  EvAddGpeReference ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvAddGpeReference (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo,
    BOOLEAN                 ClearOnEnable)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (EvAddGpeReference);


    if (GpeEventInfo->RuntimeCount == ACPI_UINT8_MAX)
    {
        return_ACPI_STATUS (AE_LIMIT);
    }

    GpeEventInfo->RuntimeCount++;
    if (GpeEventInfo->RuntimeCount == 1)
    {
        /* Enable on first reference */

        if (ClearOnEnable)
        {
            (void) AcpiHwClearGpe (GpeEventInfo);
        }

        Status = AcpiEvUpdateGpeEnableMask (GpeEventInfo);
        if (ACPI_SUCCESS (Status))
        {
            Status = AcpiEvEnableGpe (GpeEventInfo);
        }

        if (ACPI_FAILURE (Status))
        {
            GpeEventInfo->RuntimeCount--;
        }
    }

    return_ACPI_STATUS (Status);
}