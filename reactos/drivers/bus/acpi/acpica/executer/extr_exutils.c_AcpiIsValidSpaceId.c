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
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_DATA_TABLE ; 
 scalar_t__ ACPI_ADR_SPACE_FIXED_HARDWARE ; 
 scalar_t__ ACPI_NUM_PREDEFINED_REGIONS ; 
 scalar_t__ ACPI_USER_REGION_BEGIN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AcpiIsValidSpaceId (
    UINT8                   SpaceId)
{

    if ((SpaceId >= ACPI_NUM_PREDEFINED_REGIONS) &&
        (SpaceId < ACPI_USER_REGION_BEGIN) &&
        (SpaceId != ACPI_ADR_SPACE_DATA_TABLE) &&
        (SpaceId != ACPI_ADR_SPACE_FIXED_HARDWARE))
    {
        return (FALSE);
    }

    return (TRUE);
}