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
typedef  int /*<<< orphan*/ * ACPI_STRING ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PREDEFINED_NAMES ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 

ACPI_STATUS
AcpiOsPredefinedOverride(
    const ACPI_PREDEFINED_NAMES *PredefinedObject,
    ACPI_STRING                 *NewValue)
{
    if (!PredefinedObject || !NewValue)
    {
        DPRINT1("Invalid parameter\n");
        return AE_BAD_PARAMETER;
    }

    /* No override */
    *NewValue = NULL;

    return AE_OK;
}