#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_19__ {int Type; } ;
struct TYPE_18__ {int /*<<< orphan*/  Class; int /*<<< orphan*/  Node; } ;
struct TYPE_17__ {int /*<<< orphan*/  Length; } ;
struct TYPE_16__ {int /*<<< orphan*/  Length; } ;
struct TYPE_20__ {TYPE_5__ Common; TYPE_4__ Reference; TYPE_3__ Buffer; TYPE_2__ String; } ;
struct TYPE_15__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_14__ {TYPE_1__ Name; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;
typedef  TYPE_6__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;

/* Variables and functions */
 TYPE_12__* ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_6__*) ; 
 int /*<<< orphan*/  ACPI_NAMESPACE_NODE ; 
#define  ACPI_REFCLASS_NAME 134 
 int ACPI_ROUND_UP_TO_NATIVE_WORD (int) ; 
#define  ACPI_TYPE_BUFFER 133 
#define  ACPI_TYPE_INTEGER 132 
#define  ACPI_TYPE_LOCAL_REFERENCE 131 
#define  ACPI_TYPE_POWER 130 
#define  ACPI_TYPE_PROCESSOR 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int AcpiNsGetPathnameLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiUtGetReferenceName (TYPE_6__*) ; 
 int /*<<< orphan*/  UtGetSimpleObjectSize ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtGetSimpleObjectSize (
    ACPI_OPERAND_OBJECT     *InternalObject,
    ACPI_SIZE               *ObjLength)
{
    ACPI_SIZE               Length;
    ACPI_SIZE               Size;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE_PTR (UtGetSimpleObjectSize, InternalObject);


    /* Start with the length of the (external) Acpi object */

    Length = sizeof (ACPI_OBJECT);

    /* A NULL object is allowed, can be a legal uninitialized package element */

    if (!InternalObject)
    {
        /*
         * Object is NULL, just return the length of ACPI_OBJECT
         * (A NULL ACPI_OBJECT is an object of all zeroes.)
         */
        *ObjLength = ACPI_ROUND_UP_TO_NATIVE_WORD (Length);
        return_ACPI_STATUS (AE_OK);
    }

    /* A Namespace Node should never appear here */

    if (ACPI_GET_DESCRIPTOR_TYPE (InternalObject) == ACPI_DESC_TYPE_NAMED)
    {
        /* A namespace node should never get here */

        ACPI_ERROR ((AE_INFO,
            "Received a namespace node [%4.4s] "
            "where an operand object is required",
            ACPI_CAST_PTR (ACPI_NAMESPACE_NODE, InternalObject)->Name.Ascii));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    /*
     * The final length depends on the object type
     * Strings and Buffers are packed right up against the parent object and
     * must be accessed bytewise or there may be alignment problems on
     * certain processors
     */
    switch (InternalObject->Common.Type)
    {
    case ACPI_TYPE_STRING:

        Length += (ACPI_SIZE) InternalObject->String.Length + 1;
        break;

    case ACPI_TYPE_BUFFER:

        Length += (ACPI_SIZE) InternalObject->Buffer.Length;
        break;

    case ACPI_TYPE_INTEGER:
    case ACPI_TYPE_PROCESSOR:
    case ACPI_TYPE_POWER:

        /* No extra data for these types */

        break;

    case ACPI_TYPE_LOCAL_REFERENCE:

        switch (InternalObject->Reference.Class)
        {
        case ACPI_REFCLASS_NAME:
            /*
             * Get the actual length of the full pathname to this object.
             * The reference will be converted to the pathname to the object
             */
            Size = AcpiNsGetPathnameLength (InternalObject->Reference.Node);
            if (!Size)
            {
                return_ACPI_STATUS (AE_BAD_PARAMETER);
            }

            Length += ACPI_ROUND_UP_TO_NATIVE_WORD (Size);
            break;

        default:
            /*
             * No other reference opcodes are supported.
             * Notably, Locals and Args are not supported, but this may be
             * required eventually.
             */
            ACPI_ERROR ((AE_INFO, "Cannot convert to external object - "
                "unsupported Reference Class [%s] 0x%X in object %p",
                AcpiUtGetReferenceName (InternalObject),
                InternalObject->Reference.Class, InternalObject));
            Status = AE_TYPE;
            break;
        }
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Cannot convert to external object - "
            "unsupported type [%s] 0x%X in object %p",
            AcpiUtGetObjectTypeName (InternalObject),
            InternalObject->Common.Type, InternalObject));
        Status = AE_TYPE;
        break;
    }

    /*
     * Account for the space required by the object rounded up to the next
     * multiple of the machine word size. This keeps each object aligned
     * on a machine word boundary. (preventing alignment faults on some
     * machines.)
     */
    *ObjLength = ACPI_ROUND_UP_TO_NATIVE_WORD (Length);
    return_ACPI_STATUS (Status);
}