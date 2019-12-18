#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_13__ {int Type; int /*<<< orphan*/  Flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  Length; scalar_t__ Pointer; } ;
struct TYPE_11__ {int /*<<< orphan*/ * Pointer; } ;
struct TYPE_10__ {int /*<<< orphan*/  Value; } ;
struct TYPE_14__ {TYPE_4__ Common; TYPE_3__ String; TYPE_2__ Buffer; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_5__*) ; 
#define  ACPI_TYPE_BUFFER 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiGbl_IntegerByteWidth ; 
 TYPE_5__* AcpiUtCreateBufferObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExConvertToBuffer ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExConvertToBuffer (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     **ResultDesc)
{
    ACPI_OPERAND_OBJECT     *ReturnDesc;
    UINT8                   *NewBuf;


    ACPI_FUNCTION_TRACE_PTR (ExConvertToBuffer, ObjDesc);


    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_BUFFER:

        /* No conversion necessary */

        *ResultDesc = ObjDesc;
        return_ACPI_STATUS (AE_OK);


    case ACPI_TYPE_INTEGER:
        /*
         * Create a new Buffer object.
         * Need enough space for one integer
         */
        ReturnDesc = AcpiUtCreateBufferObject (AcpiGbl_IntegerByteWidth);
        if (!ReturnDesc)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Copy the integer to the buffer, LSB first */

        NewBuf = ReturnDesc->Buffer.Pointer;
        memcpy (NewBuf, &ObjDesc->Integer.Value, AcpiGbl_IntegerByteWidth);
        break;

    case ACPI_TYPE_STRING:
        /*
         * Create a new Buffer object
         * Size will be the string length
         *
         * NOTE: Add one to the string length to include the null terminator.
         * The ACPI spec is unclear on this subject, but there is existing
         * ASL/AML code that depends on the null being transferred to the new
         * buffer.
         */
        ReturnDesc = AcpiUtCreateBufferObject ((ACPI_SIZE)
            ObjDesc->String.Length + 1);
        if (!ReturnDesc)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Copy the string to the buffer */

        NewBuf = ReturnDesc->Buffer.Pointer;
        strncpy ((char *) NewBuf, (char *) ObjDesc->String.Pointer,
            ObjDesc->String.Length);
        break;

    default:

        return_ACPI_STATUS (AE_TYPE);
    }

    /* Mark buffer initialized */

    ReturnDesc->Common.Flags |= AOPOBJ_DATA_VALID;
    *ResultDesc = ReturnDesc;
    return_ACPI_STATUS (AE_OK);
}