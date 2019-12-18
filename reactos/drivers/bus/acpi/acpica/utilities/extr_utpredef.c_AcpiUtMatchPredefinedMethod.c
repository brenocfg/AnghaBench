#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* Name; } ;
struct TYPE_8__ {TYPE_1__ Info; } ;
typedef  TYPE_2__ ACPI_PREDEFINED_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,scalar_t__*) ; 
 TYPE_2__* AcpiGbl_PredefinedMethods ; 
 TYPE_2__* AcpiUtGetNextPredefinedMethod (TYPE_2__ const*) ; 

const ACPI_PREDEFINED_INFO *
AcpiUtMatchPredefinedMethod (
    char                        *Name)
{
    const ACPI_PREDEFINED_INFO  *ThisName;


    /* Quick check for a predefined name, first character must be underscore */

    if (Name[0] != '_')
    {
        return (NULL);
    }

    /* Search info table for a predefined method/object name */

    ThisName = AcpiGbl_PredefinedMethods;
    while (ThisName->Info.Name[0])
    {
        if (ACPI_COMPARE_NAMESEG (Name, ThisName->Info.Name))
        {
            return (ThisName);
        }

        ThisName = AcpiUtGetNextPredefinedMethod (ThisName);
    }

    return (NULL); /* Not found */
}