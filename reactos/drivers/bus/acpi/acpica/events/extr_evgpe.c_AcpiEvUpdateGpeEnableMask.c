#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_6__ {scalar_t__ RuntimeCount; TYPE_1__* RegisterInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  EnableForRun; int /*<<< orphan*/  EnableMask; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_GPE_REGISTER_INFO ;
typedef  TYPE_2__ ACPI_GPE_EVENT_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CLEAR_BIT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AcpiHwGetGpeRegisterBit (TYPE_2__*) ; 
 int /*<<< orphan*/  EvUpdateGpeEnableMask ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvUpdateGpeEnableMask (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo)
{
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    UINT32                  RegisterBit;


    ACPI_FUNCTION_TRACE (EvUpdateGpeEnableMask);


    GpeRegisterInfo = GpeEventInfo->RegisterInfo;
    if (!GpeRegisterInfo)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    RegisterBit = AcpiHwGetGpeRegisterBit (GpeEventInfo);

    /* Clear the run bit up front */

    ACPI_CLEAR_BIT (GpeRegisterInfo->EnableForRun, RegisterBit);

    /* Set the mask bit only if there are references to this GPE */

    if (GpeEventInfo->RuntimeCount)
    {
        ACPI_SET_BIT (GpeRegisterInfo->EnableForRun, (UINT8) RegisterBit);
    }

    GpeRegisterInfo->EnableMask = GpeRegisterInfo->EnableForRun;
    return_ACPI_STATUS (AE_OK);
}