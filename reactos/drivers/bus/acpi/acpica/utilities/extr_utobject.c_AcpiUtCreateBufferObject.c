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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_7__ {scalar_t__ Length; int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Flags; } ;
struct TYPE_8__ {TYPE_1__ Buffer; } ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 TYPE_2__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_2__*) ; 
 int /*<<< orphan*/  UtCreateBufferObject ; 
 int /*<<< orphan*/  return_PTR (TYPE_2__*) ; 

ACPI_OPERAND_OBJECT *
AcpiUtCreateBufferObject (
    ACPI_SIZE               BufferSize)
{
    ACPI_OPERAND_OBJECT     *BufferDesc;
    UINT8                   *Buffer = NULL;


    ACPI_FUNCTION_TRACE_U32 (UtCreateBufferObject, BufferSize);


    /* Create a new Buffer object */

    BufferDesc = AcpiUtCreateInternalObject (ACPI_TYPE_BUFFER);
    if (!BufferDesc)
    {
        return_PTR (NULL);
    }

    /* Create an actual buffer only if size > 0 */

    if (BufferSize > 0)
    {
        /* Allocate the actual buffer */

        Buffer = ACPI_ALLOCATE_ZEROED (BufferSize);
        if (!Buffer)
        {
            ACPI_ERROR ((AE_INFO, "Could not allocate size %u",
                (UINT32) BufferSize));

            AcpiUtRemoveReference (BufferDesc);
            return_PTR (NULL);
        }
    }

    /* Complete buffer object initialization */

    BufferDesc->Buffer.Flags |= AOPOBJ_DATA_VALID;
    BufferDesc->Buffer.Pointer = Buffer;
    BufferDesc->Buffer.Length = (UINT32) BufferSize;

    /* Return the new buffer descriptor */

    return_PTR (BufferDesc);
}