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
typedef  size_t ACPI_OBJECT_TYPE ;

/* Variables and functions */
 size_t ACPI_TYPE_INVALID ; 
 char const* AcpiGbl_BadType ; 
 char const** AcpiGbl_NsTypeNames ; 

const char *
AcpiUtGetTypeName (
    ACPI_OBJECT_TYPE        Type)
{

    if (Type > ACPI_TYPE_INVALID)
    {
        return (AcpiGbl_BadType);
    }

    return (AcpiGbl_NsTypeNames[Type]);
}