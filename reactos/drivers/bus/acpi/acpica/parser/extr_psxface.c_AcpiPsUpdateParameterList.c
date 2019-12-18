#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {scalar_t__* Parameters; } ;
typedef  TYPE_1__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiUtUpdateObjectReference (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AcpiPsUpdateParameterList (
    ACPI_EVALUATE_INFO      *Info,
    UINT16                  Action)
{
    UINT32                  i;


    if (Info->Parameters)
    {
        /* Update reference count for each parameter */

        for (i = 0; Info->Parameters[i]; i++)
        {
            /* Ignore errors, just do them all */

            (void) AcpiUtUpdateObjectReference (
                Info->Parameters[i], Action);
        }
    }
}