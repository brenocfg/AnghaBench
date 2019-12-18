#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_2__ {int /*<<< orphan*/  SleepStatus; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SLEEP_TYPE_INVALID ; 
 int /*<<< orphan*/  ACPI_SST_WAKING ; 
 int /*<<< orphan*/  ACPI_SST_WORKING ; 
 scalar_t__ ACPI_X_WAKE_STATUS ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiGbl_SleepTypeA ; 
 int /*<<< orphan*/  AcpiGbl_SystemAwakeAndRunning ; 
 int /*<<< orphan*/  AcpiHwExecuteSleepMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HwExtendedWake ; 
 int /*<<< orphan*/  METHOD_PATHNAME__SST ; 
 int /*<<< orphan*/  METHOD_PATHNAME__WAK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwExtendedWake (
    UINT8                   SleepState)
{
    ACPI_FUNCTION_TRACE (HwExtendedWake);


    /* Ensure EnterSleepStatePrep -> EnterSleepState ordering */

    AcpiGbl_SleepTypeA = ACPI_SLEEP_TYPE_INVALID;

    /* Execute the wake methods */

    AcpiHwExecuteSleepMethod (METHOD_PATHNAME__SST, ACPI_SST_WAKING);
    AcpiHwExecuteSleepMethod (METHOD_PATHNAME__WAK, SleepState);

    /*
     * Some BIOS code assumes that WAK_STS will be cleared on resume
     * and use it to determine whether the system is rebooting or
     * resuming. Clear WAK_STS for compatibility.
     */
    (void) AcpiWrite ((UINT64) ACPI_X_WAKE_STATUS, &AcpiGbl_FADT.SleepStatus);
    AcpiGbl_SystemAwakeAndRunning = TRUE;

    AcpiHwExecuteSleepMethod (METHOD_PATHNAME__SST, ACPI_SST_WORKING);
    return_ACPI_STATUS (AE_OK);
}