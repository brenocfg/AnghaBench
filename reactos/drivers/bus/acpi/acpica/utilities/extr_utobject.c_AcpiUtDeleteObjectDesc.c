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
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiGbl_OperandCache ; 
 int /*<<< orphan*/  AcpiOsReleaseObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtDeleteObjectDesc ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiUtDeleteObjectDesc (
    ACPI_OPERAND_OBJECT     *Object)
{
    ACPI_FUNCTION_TRACE_PTR (UtDeleteObjectDesc, Object);


    /* Object must be of type ACPI_OPERAND_OBJECT */

    if (ACPI_GET_DESCRIPTOR_TYPE (Object) != ACPI_DESC_TYPE_OPERAND)
    {
        ACPI_ERROR ((AE_INFO,
            "%p is not an ACPI Operand object [%s]", Object,
            AcpiUtGetDescriptorName (Object)));
        return_VOID;
    }

    (void) AcpiOsReleaseObject (AcpiGbl_OperandCache, Object);
    return_VOID;
}