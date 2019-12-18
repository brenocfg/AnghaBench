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
struct TYPE_3__ {scalar_t__ StringLength; scalar_t__ StringPtr; } ;
typedef  int /*<<< orphan*/  ACPI_RS_LENGTH ;
typedef  TYPE_1__ ACPI_RESOURCE_SOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 

__attribute__((used)) static ACPI_RS_LENGTH
AcpiRsStructOptionLength (
    ACPI_RESOURCE_SOURCE    *ResourceSource)
{
    ACPI_FUNCTION_ENTRY ();


    /*
     * If the ResourceSource string is valid, return the size of the string
     * (StringLength includes the NULL terminator) plus the size of the
     * ResourceSourceIndex (1).
     */
    if (ResourceSource->StringPtr)
    {
        return ((ACPI_RS_LENGTH) (ResourceSource->StringLength + 1));
    }

    return (0);
}