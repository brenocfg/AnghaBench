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
struct TYPE_7__ {scalar_t__ Type; } ;
struct TYPE_8__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_2__*) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AcpiUtGetPackageObjectSize (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetSimpleObjectSize (TYPE_2__*,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiUtGetObjectSize (
    ACPI_OPERAND_OBJECT     *InternalObject,
    ACPI_SIZE               *ObjLength)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_ENTRY ();


    if ((ACPI_GET_DESCRIPTOR_TYPE (InternalObject) ==
            ACPI_DESC_TYPE_OPERAND) &&
        (InternalObject->Common.Type == ACPI_TYPE_PACKAGE))
    {
        Status = AcpiUtGetPackageObjectSize (InternalObject, ObjLength);
    }
    else
    {
        Status = AcpiUtGetSimpleObjectSize (InternalObject, ObjLength);
    }

    return (Status);
}