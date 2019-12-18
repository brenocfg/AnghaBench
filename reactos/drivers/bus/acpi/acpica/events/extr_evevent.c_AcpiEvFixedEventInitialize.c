#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/ * Context; int /*<<< orphan*/ * Handler; } ;
struct TYPE_3__ {int EnableRegisterId; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DISABLE_EVENT ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_NUM_FIXED_EVENTS ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__* AcpiGbl_FixedEventHandlers ; 
 TYPE_1__* AcpiGbl_FixedEventInfo ; 
 int /*<<< orphan*/  AcpiWriteBitRegister (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiEvFixedEventInitialize (
    void)
{
    UINT32                  i;
    ACPI_STATUS             Status;


    /*
     * Initialize the structure that keeps track of fixed event handlers and
     * enable the fixed events.
     */
    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        AcpiGbl_FixedEventHandlers[i].Handler = NULL;
        AcpiGbl_FixedEventHandlers[i].Context = NULL;

        /* Disable the fixed event */

        if (AcpiGbl_FixedEventInfo[i].EnableRegisterId != 0xFF)
        {
            Status = AcpiWriteBitRegister (
                AcpiGbl_FixedEventInfo[i].EnableRegisterId,
                ACPI_DISABLE_EVENT);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }
    }

    return (AE_OK);
}