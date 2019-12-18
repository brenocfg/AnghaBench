#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_7__ {int /*<<< orphan*/  Value; } ;
struct TYPE_6__ {scalar_t__ Type; } ;
struct TYPE_8__ {TYPE_2__ Integer; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_3__*) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int AcpiGbl_IntegerByteWidth ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AcpiExTruncateFor32bitTable (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{

    ACPI_FUNCTION_ENTRY ();


    /*
     * Object must be a valid number and we must be executing
     * a control method. Object could be NS node for AML_INT_NAMEPATH_OP.
     */
    if ((!ObjDesc) ||
        (ACPI_GET_DESCRIPTOR_TYPE (ObjDesc) != ACPI_DESC_TYPE_OPERAND) ||
        (ObjDesc->Common.Type != ACPI_TYPE_INTEGER))
    {
        return (FALSE);
    }

    if ((AcpiGbl_IntegerByteWidth == 4) &&
        (ObjDesc->Integer.Value > (UINT64) ACPI_UINT32_MAX))
    {
        /*
         * We are executing in a 32-bit ACPI table. Truncate
         * the value to 32 bits by zeroing out the upper 32-bit field
         */
        ObjDesc->Integer.Value &= (UINT64) ACPI_UINT32_MAX;
        return (TRUE);
    }

    return (FALSE);
}