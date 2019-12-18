#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Type; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorName (TYPE_2__*) ; 
 char* AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtGetObjectTypeName ; 
 int /*<<< orphan*/  return_STR (char*) ; 

const char *
AcpiUtGetObjectTypeName (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_FUNCTION_TRACE (UtGetObjectTypeName);


    if (!ObjDesc)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Null Object Descriptor\n"));
        return_STR ("[NULL Object Descriptor]");
    }

    /* These descriptor types share a common area */

    if ((ACPI_GET_DESCRIPTOR_TYPE (ObjDesc) != ACPI_DESC_TYPE_OPERAND) &&
        (ACPI_GET_DESCRIPTOR_TYPE (ObjDesc) != ACPI_DESC_TYPE_NAMED))
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "Invalid object descriptor type: 0x%2.2X [%s] (%p)\n",
            ACPI_GET_DESCRIPTOR_TYPE (ObjDesc),
            AcpiUtGetDescriptorName (ObjDesc), ObjDesc));

        return_STR ("Invalid object");
    }

    return_STR (AcpiUtGetTypeName (ObjDesc->Common.Type));
}