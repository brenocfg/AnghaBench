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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_ERROR (char const*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SET_DESCRIPTOR_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_OperandCache ; 
 int /*<<< orphan*/ * AcpiOsAcquireObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtAllocateObjectDescDbg ; 
 int /*<<< orphan*/  return_PTR (int /*<<< orphan*/ *) ; 

void *
AcpiUtAllocateObjectDescDbg (
    const char              *ModuleName,
    UINT32                  LineNumber,
    UINT32                  ComponentId)
{
    ACPI_OPERAND_OBJECT     *Object;


    ACPI_FUNCTION_TRACE (UtAllocateObjectDescDbg);


    Object = AcpiOsAcquireObject (AcpiGbl_OperandCache);
    if (!Object)
    {
        ACPI_ERROR ((ModuleName, LineNumber,
            "Could not allocate an object descriptor"));

        return_PTR (NULL);
    }

    /* Mark the descriptor type */

    ACPI_SET_DESCRIPTOR_TYPE (Object, ACPI_DESC_TYPE_OPERAND);

    ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS, "%p Size %X\n",
        Object, (UINT32) sizeof (ACPI_OPERAND_OBJECT)));

    return_PTR (Object);
}