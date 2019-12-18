#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
struct TYPE_12__ {scalar_t__ AmlOpcode; TYPE_4__* Next; int /*<<< orphan*/ * Node; } ;
struct TYPE_11__ {int /*<<< orphan*/  Name; } ;
struct TYPE_14__ {TYPE_2__ Common; TYPE_1__ Named; } ;
struct TYPE_13__ {int ParseFlags; int Opcode; int /*<<< orphan*/  ScopeInfo; scalar_t__ MethodNode; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int ACPI_NS_OVERRIDE_IF_FOUND ; 
 int ACPI_NS_TEMPORARY ; 
 int ACPI_PARSE_DEFERRED_OP ; 
 int ACPI_PARSE_EXECUTE ; 
 int ACPI_PARSE_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_BANK_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_INDEX_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REGION_FIELD ; 
 scalar_t__ AE_ALREADY_EXISTS ; 
 scalar_t__ AE_AML_INTERNAL ; 
 scalar_t__ AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
#define  AML_BANK_FIELD_OP 130 
#define  AML_FIELD_OP 129 
#define  AML_INDEX_FIELD_OP 128 
 scalar_t__ AML_INT_NAMEDFIELD_OP ; 
 scalar_t__ AcpiNsLookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ **) ; 
 TYPE_4__* AcpiPsGetArg (TYPE_4__*,int) ; 
 int /*<<< orphan*/  DsInitFieldObjects ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiDsInitFieldObjects (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Arg = NULL;
    ACPI_NAMESPACE_NODE     *Node;
    UINT8                   Type = 0;
    UINT32                  Flags;


    ACPI_FUNCTION_TRACE_PTR (DsInitFieldObjects, Op);


    /* Execute flag should always be set when this function is entered */

    if (!(WalkState->ParseFlags & ACPI_PARSE_EXECUTE))
    {
        if (WalkState->ParseFlags & ACPI_PARSE_DEFERRED_OP)
        {
            /* BankField Op is deferred, just return OK */

            return_ACPI_STATUS (AE_OK);
        }

        ACPI_ERROR ((AE_INFO,
            "Parse deferred mode is not set"));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    /*
     * Get the FieldList argument for this opcode. This is the start of the
     * list of field elements.
     */
    switch (WalkState->Opcode)
    {
    case AML_FIELD_OP:

        Arg = AcpiPsGetArg (Op, 2);
        Type = ACPI_TYPE_LOCAL_REGION_FIELD;
        break;

    case AML_BANK_FIELD_OP:

        Arg = AcpiPsGetArg (Op, 4);
        Type = ACPI_TYPE_LOCAL_BANK_FIELD;
        break;

    case AML_INDEX_FIELD_OP:

        Arg = AcpiPsGetArg (Op, 3);
        Type = ACPI_TYPE_LOCAL_INDEX_FIELD;
        break;

    default:

        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Creating new namespace node(s), should not already exist */

    Flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
        ACPI_NS_ERROR_IF_FOUND;

    /*
     * Mark node(s) temporary if we are executing a normal control
     * method. (Don't mark if this is a module-level code method)
     */
    if (WalkState->MethodNode &&
        !(WalkState->ParseFlags & ACPI_PARSE_MODULE_LEVEL))
    {
        Flags |= ACPI_NS_TEMPORARY;
    }

#ifdef ACPI_EXEC_APP
        Flags |= ACPI_NS_OVERRIDE_IF_FOUND;
#endif
    /*
     * Walk the list of entries in the FieldList
     * Note: FieldList can be of zero length. In this case, Arg will be NULL.
     */
    while (Arg)
    {
        /*
         * Ignore OFFSET/ACCESSAS/CONNECTION terms here; we are only interested
         * in the field names in order to enter them into the namespace.
         */
        if (Arg->Common.AmlOpcode == AML_INT_NAMEDFIELD_OP)
        {
            Status = AcpiNsLookup (WalkState->ScopeInfo,
                (char *) &Arg->Named.Name, Type, ACPI_IMODE_LOAD_PASS1,
                Flags, WalkState, &Node);
            if (ACPI_FAILURE (Status))
            {
                ACPI_ERROR_NAMESPACE (WalkState->ScopeInfo,
                    (char *) &Arg->Named.Name, Status);
                if (Status != AE_ALREADY_EXISTS)
                {
                    return_ACPI_STATUS (Status);
                }

                /* Name already exists, just ignore this error */
            }

            Arg->Common.Node = Node;
        }

        /* Get the next field element in the list */

        Arg = Arg->Common.Next;
    }

    return_ACPI_STATUS (AE_OK);
}