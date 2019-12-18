#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* Handler; TYPE_3__* Next; int /*<<< orphan*/  SpaceId; int /*<<< orphan*/  Node; } ;
struct TYPE_7__ {TYPE_3__* RegionList; } ;
struct TYPE_9__ {TYPE_2__ Region; TYPE_1__ AddressSpace; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtAddReference (TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetRegionName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvAttachRegion ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvAttachRegion (
    ACPI_OPERAND_OBJECT     *HandlerObj,
    ACPI_OPERAND_OBJECT     *RegionObj,
    BOOLEAN                 AcpiNsIsLocked)
{

    ACPI_FUNCTION_TRACE (EvAttachRegion);


    /* Install the region's handler */

    if (RegionObj->Region.Handler)
    {
        return_ACPI_STATUS (AE_ALREADY_EXISTS);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
        "Adding Region [%4.4s] %p to address handler %p [%s]\n",
        AcpiUtGetNodeName (RegionObj->Region.Node),
        RegionObj, HandlerObj,
        AcpiUtGetRegionName (RegionObj->Region.SpaceId)));

    /* Link this region to the front of the handler's list */

    RegionObj->Region.Next = HandlerObj->AddressSpace.RegionList;
    HandlerObj->AddressSpace.RegionList = RegionObj;
    RegionObj->Region.Handler = HandlerObj;
    AcpiUtAddReference (HandlerObj);

    return_ACPI_STATUS (AE_OK);
}