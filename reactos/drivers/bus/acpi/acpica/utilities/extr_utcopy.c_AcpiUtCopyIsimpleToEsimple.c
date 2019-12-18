#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_33__ {int /*<<< orphan*/  PblkLength; int /*<<< orphan*/  PblkAddress; int /*<<< orphan*/  ProcId; } ;
struct TYPE_32__ {int /*<<< orphan*/  Node; int /*<<< orphan*/  Class; } ;
struct TYPE_31__ {int /*<<< orphan*/  ActualType; int /*<<< orphan*/  Handle; } ;
struct TYPE_30__ {int /*<<< orphan*/  Value; } ;
struct TYPE_29__ {int /*<<< orphan*/  Value; } ;
struct TYPE_28__ {int /*<<< orphan*/  Length; scalar_t__ Pointer; } ;
struct TYPE_27__ {int /*<<< orphan*/  Length; scalar_t__ Pointer; } ;
struct TYPE_26__ {int /*<<< orphan*/  Length; int /*<<< orphan*/ * Pointer; } ;
struct TYPE_25__ {char* Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_20__ {int /*<<< orphan*/  ResourceOrder; int /*<<< orphan*/  SystemLevel; } ;
struct TYPE_24__ {int Type; TYPE_11__ PowerResource; TYPE_9__ Processor; TYPE_7__ Reference; TYPE_5__ Integer; TYPE_2__ Buffer; TYPE_1__ String; } ;
struct TYPE_22__ {int Type; } ;
struct TYPE_21__ {int /*<<< orphan*/  ResourceOrder; int /*<<< orphan*/  SystemLevel; } ;
struct TYPE_19__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Address; int /*<<< orphan*/  ProcId; } ;
struct TYPE_23__ {TYPE_13__ Common; TYPE_12__ PowerResource; TYPE_10__ Processor; TYPE_8__ Reference; TYPE_6__ Integer; TYPE_4__ Buffer; TYPE_3__ String; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_14__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_15__ ACPI_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_REFCLASS_NAME 134 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 133 
#define  ACPI_TYPE_INTEGER 132 
#define  ACPI_TYPE_LOCAL_REFERENCE 131 
#define  ACPI_TYPE_POWER 130 
#define  ACPI_TYPE_PROCESSOR 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  AcpiNsGetType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int) ; 
 int /*<<< orphan*/  UtCopyIsimpleToEsimple ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_15__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtCopyIsimpleToEsimple (
    ACPI_OPERAND_OBJECT     *InternalObject,
    ACPI_OBJECT             *ExternalObject,
    UINT8                   *DataSpace,
    ACPI_SIZE               *BufferSpaceUsed)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (UtCopyIsimpleToEsimple);


    *BufferSpaceUsed = 0;

    /*
     * Check for NULL object case (could be an uninitialized
     * package element)
     */
    if (!InternalObject)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Always clear the external object */

    memset (ExternalObject, 0, sizeof (ACPI_OBJECT));

    /*
     * In general, the external object will be the same type as
     * the internal object
     */
    ExternalObject->Type = InternalObject->Common.Type;

    /* However, only a limited number of external types are supported */

    switch (InternalObject->Common.Type)
    {
    case ACPI_TYPE_STRING:

        ExternalObject->String.Pointer = (char *) DataSpace;
        ExternalObject->String.Length  = InternalObject->String.Length;
        *BufferSpaceUsed = ACPI_ROUND_UP_TO_NATIVE_WORD (
            (ACPI_SIZE) InternalObject->String.Length + 1);

        memcpy ((void *) DataSpace,
            (void *) InternalObject->String.Pointer,
            (ACPI_SIZE) InternalObject->String.Length + 1);
        break;

    case ACPI_TYPE_BUFFER:

        ExternalObject->Buffer.Pointer = DataSpace;
        ExternalObject->Buffer.Length  = InternalObject->Buffer.Length;
        *BufferSpaceUsed = ACPI_ROUND_UP_TO_NATIVE_WORD (
            InternalObject->String.Length);

        memcpy ((void *) DataSpace,
            (void *) InternalObject->Buffer.Pointer,
            InternalObject->Buffer.Length);
        break;

    case ACPI_TYPE_INTEGER:

        ExternalObject->Integer.Value = InternalObject->Integer.Value;
        break;

    case ACPI_TYPE_LOCAL_REFERENCE:

        /* This is an object reference. */

        switch (InternalObject->Reference.Class)
        {
        case ACPI_REFCLASS_NAME:
            /*
             * For namepath, return the object handle ("reference")
             * We are referring to the namespace node
             */
            ExternalObject->Reference.Handle =
                InternalObject->Reference.Node;
            ExternalObject->Reference.ActualType =
                AcpiNsGetType (InternalObject->Reference.Node);
            break;

        default:

            /* All other reference types are unsupported */

            return_ACPI_STATUS (AE_TYPE);
        }
        break;

    case ACPI_TYPE_PROCESSOR:

        ExternalObject->Processor.ProcId =
            InternalObject->Processor.ProcId;
        ExternalObject->Processor.PblkAddress =
            InternalObject->Processor.Address;
        ExternalObject->Processor.PblkLength =
            InternalObject->Processor.Length;
        break;

    case ACPI_TYPE_POWER:

        ExternalObject->PowerResource.SystemLevel =
            InternalObject->PowerResource.SystemLevel;

        ExternalObject->PowerResource.ResourceOrder =
            InternalObject->PowerResource.ResourceOrder;
        break;

    default:
        /*
         * There is no corresponding external object type
         */
        ACPI_ERROR ((AE_INFO,
            "Unsupported object type, cannot convert to external object: %s",
            AcpiUtGetTypeName (InternalObject->Common.Type)));

        return_ACPI_STATUS (AE_SUPPORT);
    }

    return_ACPI_STATUS (Status);
}