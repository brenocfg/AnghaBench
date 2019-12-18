#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_24__ {int /*<<< orphan*/ * Node; } ;
struct TYPE_22__ {int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  AmlStart; } ;
struct TYPE_21__ {TYPE_9__* NextObject; } ;
struct TYPE_27__ {TYPE_6__ BufferField; TYPE_4__ Extra; TYPE_3__ Common; } ;
struct TYPE_23__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Data; } ;
struct TYPE_19__ {int /*<<< orphan*/  String; } ;
struct TYPE_20__ {scalar_t__ AmlOpcode; int /*<<< orphan*/ * Node; TYPE_1__ Value; } ;
struct TYPE_26__ {TYPE_5__ Named; TYPE_2__ Common; } ;
struct TYPE_25__ {int ParseFlags; int /*<<< orphan*/  ScopeInfo; scalar_t__ MethodNode; int /*<<< orphan*/ * DeferredNode; } ;
typedef  TYPE_7__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_8__ ACPI_PARSE_OBJECT ;
typedef  TYPE_9__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int ACPI_NS_TEMPORARY ; 
 int ACPI_PARSE_EXECUTE ; 
 int ACPI_PARSE_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_CREATE_FIELD_OP ; 
 int /*<<< orphan*/  AcpiNsAttachObject (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* AcpiNsGetAttachedObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiNsLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_7__*,int /*<<< orphan*/ **) ; 
 TYPE_8__* AcpiPsGetArg (TYPE_8__*,int) ; 
 TYPE_9__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_9__*) ; 
 int /*<<< orphan*/  DsCreateBufferField ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsCreateBufferField (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_PARSE_OBJECT       *Arg;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *SecondDesc = NULL;
    UINT32                  Flags;


    ACPI_FUNCTION_TRACE (DsCreateBufferField);


    /*
     * Get the NameString argument (name of the new BufferField)
     */
    if (Op->Common.AmlOpcode == AML_CREATE_FIELD_OP)
    {
        /* For CreateField, name is the 4th argument */

        Arg = AcpiPsGetArg (Op, 3);
    }
    else
    {
        /* For all other CreateXXXField operators, name is the 3rd argument */

        Arg = AcpiPsGetArg (Op, 2);
    }

    if (!Arg)
    {
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    if (WalkState->DeferredNode)
    {
        Node = WalkState->DeferredNode;
    }
    else
    {
        /* Execute flag should always be set when this function is entered */

        if (!(WalkState->ParseFlags & ACPI_PARSE_EXECUTE))
        {
            ACPI_ERROR ((AE_INFO,
                "Parse execute mode is not set"));
            return_ACPI_STATUS (AE_AML_INTERNAL);
        }

        /* Creating new namespace node, should not already exist */

        Flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
            ACPI_NS_ERROR_IF_FOUND;

        /*
         * Mark node temporary if we are executing a normal control
         * method. (Don't mark if this is a module-level code method)
         */
        if (WalkState->MethodNode &&
            !(WalkState->ParseFlags & ACPI_PARSE_MODULE_LEVEL))
        {
            Flags |= ACPI_NS_TEMPORARY;
        }

        /* Enter the NameString into the namespace */

        Status = AcpiNsLookup (WalkState->ScopeInfo,
            Arg->Common.Value.String, ACPI_TYPE_ANY,
            ACPI_IMODE_LOAD_PASS1, Flags, WalkState, &Node);
        if (ACPI_FAILURE (Status))
        {
            ACPI_ERROR_NAMESPACE (WalkState->ScopeInfo,
                Arg->Common.Value.String, Status);
            return_ACPI_STATUS (Status);
        }
    }

    /*
     * We could put the returned object (Node) on the object stack for later,
     * but for now, we will put it in the "op" object that the parser uses,
     * so we can get it again at the end of this scope.
     */
    Op->Common.Node = Node;

    /*
     * If there is no object attached to the node, this node was just created
     * and we need to create the field object. Otherwise, this was a lookup
     * of an existing node and we don't want to create the field object again.
     */
    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (ObjDesc)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /*
     * The Field definition is not fully parsed at this time.
     * (We must save the address of the AML for the buffer and index operands)
     */

    /* Create the buffer field object */

    ObjDesc = AcpiUtCreateInternalObject (ACPI_TYPE_BUFFER_FIELD);
    if (!ObjDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /*
     * Remember location in AML stream of the field unit opcode and operands
     * -- since the buffer and index operands must be evaluated.
     */
    SecondDesc = ObjDesc->Common.NextObject;
    SecondDesc->Extra.AmlStart = Op->Named.Data;
    SecondDesc->Extra.AmlLength = Op->Named.Length;
    ObjDesc->BufferField.Node = Node;

    /* Attach constructed field descriptors to parent node */

    Status = AcpiNsAttachObject (Node, ObjDesc, ACPI_TYPE_BUFFER_FIELD);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }


Cleanup:

    /* Remove local reference to the object */

    AcpiUtRemoveReference (ObjDesc);
    return_ACPI_STATUS (Status);
}