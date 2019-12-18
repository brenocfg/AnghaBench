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
struct TYPE_5__ {int ExpectedBtypes; } ;
struct TYPE_6__ {TYPE_1__ Info; } ;
typedef  TYPE_2__ ACPI_PREDEFINED_INFO ;

/* Variables and functions */
 int ACPI_RTYPE_ALL ; 
 int ACPI_RTYPE_PACKAGE ; 

const ACPI_PREDEFINED_INFO *
AcpiUtGetNextPredefinedMethod (
    const ACPI_PREDEFINED_INFO  *ThisName)
{

    /*
     * Skip next entry in the table if this name returns a Package
     * (next entry contains the package info)
     */
    if ((ThisName->Info.ExpectedBtypes & ACPI_RTYPE_PACKAGE) &&
        (ThisName->Info.ExpectedBtypes != ACPI_RTYPE_ALL))
    {
        ThisName++;
    }

    ThisName++;
    return (ThisName);
}