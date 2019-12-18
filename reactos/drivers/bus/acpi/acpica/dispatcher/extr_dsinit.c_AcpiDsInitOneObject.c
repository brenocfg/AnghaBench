#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_12__ {scalar_t__ OwnerId; int /*<<< orphan*/  DeviceCount; int /*<<< orphan*/  NonSerialMethodCount; int /*<<< orphan*/  SerializedMethodCount; int /*<<< orphan*/  SerialMethodCount; int /*<<< orphan*/  MethodCount; int /*<<< orphan*/  OpRegionCount; int /*<<< orphan*/  ObjectCount; } ;
struct TYPE_11__ {scalar_t__ OwnerId; } ;
struct TYPE_9__ {int InfoFlags; } ;
struct TYPE_10__ {TYPE_1__ Method; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_4__ ACPI_INIT_WALK_INFO ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_METHOD_SERIALIZED ; 
#define  ACPI_TYPE_DEVICE 130 
#define  ACPI_TYPE_METHOD 129 
#define  ACPI_TYPE_REGION 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDsAutoSerializeMethod (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDsInitializeRegion (scalar_t__) ; 
 int /*<<< orphan*/  AcpiGbl_AutoSerializeMethods ; 
 TYPE_2__* AcpiNsGetAttachedObject (TYPE_3__*) ; 
 int AcpiNsGetType (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (scalar_t__) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDsInitOneObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_INIT_WALK_INFO     *Info = (ACPI_INIT_WALK_INFO *) Context;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ObjDesc;


    ACPI_FUNCTION_ENTRY ();


    /*
     * We are only interested in NS nodes owned by the table that
     * was just loaded
     */
    if (Node->OwnerId != Info->OwnerId)
    {
        return (AE_OK);
    }

    Info->ObjectCount++;

    /* And even then, we are only interested in a few object types */

    switch (AcpiNsGetType (ObjHandle))
    {
    case ACPI_TYPE_REGION:

        Status = AcpiDsInitializeRegion (ObjHandle);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "During Region initialization %p [%4.4s]",
                ObjHandle, AcpiUtGetNodeName (ObjHandle)));
        }

        Info->OpRegionCount++;
        break;

    case ACPI_TYPE_METHOD:
        /*
         * Auto-serialization support. We will examine each method that is
         * NotSerialized to determine if it creates any Named objects. If
         * it does, it will be marked serialized to prevent problems if
         * the method is entered by two or more threads and an attempt is
         * made to create the same named object twice -- which results in
         * an AE_ALREADY_EXISTS exception and method abort.
         */
        Info->MethodCount++;
        ObjDesc = AcpiNsGetAttachedObject (Node);
        if (!ObjDesc)
        {
            break;
        }

        /* Ignore if already serialized */

        if (ObjDesc->Method.InfoFlags & ACPI_METHOD_SERIALIZED)
        {
            Info->SerialMethodCount++;
            break;
        }

        if (AcpiGbl_AutoSerializeMethods)
        {
            /* Parse/scan method and serialize it if necessary */

            AcpiDsAutoSerializeMethod (Node, ObjDesc);
            if (ObjDesc->Method.InfoFlags & ACPI_METHOD_SERIALIZED)
            {
                /* Method was just converted to Serialized */

                Info->SerialMethodCount++;
                Info->SerializedMethodCount++;
                break;
            }
        }

        Info->NonSerialMethodCount++;
        break;

    case ACPI_TYPE_DEVICE:

        Info->DeviceCount++;
        break;

    default:

        break;
    }

    /*
     * We ignore errors from above, and always return OK, since
     * we don't want to abort the walk on a single error.
     */
    return (AE_OK);
}