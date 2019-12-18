#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  RuntimeCount; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_GPE_EVENT_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GPE_DISABLE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvUpdateGpeEnableMask (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiHwLowSetGpe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvRemoveGpeReference ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvRemoveGpeReference (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (EvRemoveGpeReference);


    if (!GpeEventInfo->RuntimeCount)
    {
        return_ACPI_STATUS (AE_LIMIT);
    }

    GpeEventInfo->RuntimeCount--;
    if (!GpeEventInfo->RuntimeCount)
    {
        /* Disable on last reference */

        Status = AcpiEvUpdateGpeEnableMask (GpeEventInfo);
        if (ACPI_SUCCESS (Status))
        {
            Status = AcpiHwLowSetGpe (GpeEventInfo, ACPI_GPE_DISABLE);
        }

        if (ACPI_FAILURE (Status))
        {
            GpeEventInfo->RuntimeCount++;
        }
    }

    return_ACPI_STATUS (Status);
}