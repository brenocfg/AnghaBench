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
typedef  scalar_t__ UINT32 ;
struct TYPE_7__ {char* Pointer; scalar_t__ Length; } ;
struct TYPE_8__ {TYPE_1__ String; } ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_2__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_2__*) ; 
 int /*<<< orphan*/  UtCreateStringObject ; 
 int /*<<< orphan*/  return_PTR (TYPE_2__*) ; 

ACPI_OPERAND_OBJECT *
AcpiUtCreateStringObject (
    ACPI_SIZE               StringSize)
{
    ACPI_OPERAND_OBJECT     *StringDesc;
    char                    *String;


    ACPI_FUNCTION_TRACE_U32 (UtCreateStringObject, StringSize);


    /* Create a new String object */

    StringDesc = AcpiUtCreateInternalObject (ACPI_TYPE_STRING);
    if (!StringDesc)
    {
        return_PTR (NULL);
    }

    /*
     * Allocate the actual string buffer -- (Size + 1) for NULL terminator.
     * NOTE: Zero-length strings are NULL terminated
     */
    String = ACPI_ALLOCATE_ZEROED (StringSize + 1);
    if (!String)
    {
        ACPI_ERROR ((AE_INFO, "Could not allocate size %u",
            (UINT32) StringSize));

        AcpiUtRemoveReference (StringDesc);
        return_PTR (NULL);
    }

    /* Complete string object initialization */

    StringDesc->String.Pointer = String;
    StringDesc->String.Length = (UINT32) StringSize;

    /* Return the new string descriptor */

    return_PTR (StringDesc);
}