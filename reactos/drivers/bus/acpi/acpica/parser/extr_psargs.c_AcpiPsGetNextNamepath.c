#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_39__ {char* Name; } ;
struct TYPE_40__ {TYPE_8__ Value; TYPE_7__* Parent; TYPE_14__* Node; } ;
struct TYPE_37__ {scalar_t__ AmlOpcode; } ;
struct TYPE_38__ {TYPE_6__ Common; } ;
struct TYPE_35__ {scalar_t__ AmlOpcode; } ;
struct TYPE_36__ {TYPE_4__ Common; } ;
struct TYPE_34__ {int ParamCount; } ;
struct TYPE_33__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_32__ {int /*<<< orphan*/ * Aml; } ;
struct TYPE_31__ {scalar_t__ Type; TYPE_2__ Name; } ;
struct TYPE_30__ {TYPE_3__ Method; } ;
struct TYPE_29__ {TYPE_9__ Common; } ;
struct TYPE_28__ {int /*<<< orphan*/ * Aml; } ;
struct TYPE_27__ {int ArgCount; int ParseFlags; int /*<<< orphan*/  ScopeInfo; TYPE_5__* Op; TYPE_1__ ParserState; int /*<<< orphan*/  ArgTypes; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_10__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_11__ ACPI_PARSE_STATE ;
typedef  TYPE_12__ ACPI_PARSE_OBJECT ;
typedef  TYPE_13__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_14__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_SEARCH_PARENT ; 
 int ACPI_PARSE_EXECUTE ; 
 int ACPI_PARSE_MODE_MASK ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 scalar_t__ AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AML_CONDITIONAL_REF_OF_OP ; 
 int /*<<< orphan*/  AML_INT_METHODCALL_OP ; 
 int /*<<< orphan*/  AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_PACKAGE_OP ; 
 scalar_t__ AML_VARIABLE_PACKAGE_OP ; 
 scalar_t__ ARGP_SUPERNAME ; 
 scalar_t__ ARGP_TARGET ; 
 scalar_t__ AcpiDsMethodError (scalar_t__,TYPE_10__*) ; 
 TYPE_13__* AcpiNsGetAttachedObject (TYPE_14__*) ; 
 scalar_t__ AcpiNsLookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_14__**) ; 
 TYPE_12__* AcpiPsAllocOp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiPsAppendArg (TYPE_12__*,TYPE_12__*) ; 
 char* AcpiPsGetNextNamestring (TYPE_11__*) ; 
 int /*<<< orphan*/  AcpiPsInitOp (TYPE_12__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CURRENT_ARG_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsGetNextNamepath ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiPsGetNextNamepath (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_STATE        *ParserState,
    ACPI_PARSE_OBJECT       *Arg,
    BOOLEAN                 PossibleMethodCall)
{
    ACPI_STATUS             Status;
    char                    *Path;
    ACPI_PARSE_OBJECT       *NameOp;
    ACPI_OPERAND_OBJECT     *MethodDesc;
    ACPI_NAMESPACE_NODE     *Node;
    UINT8                   *Start = ParserState->Aml;


    ACPI_FUNCTION_TRACE (PsGetNextNamepath);


    Path = AcpiPsGetNextNamestring (ParserState);
    AcpiPsInitOp (Arg, AML_INT_NAMEPATH_OP);

    /* Null path case is allowed, just exit */

    if (!Path)
    {
        Arg->Common.Value.Name = Path;
        return_ACPI_STATUS (AE_OK);
    }

    /*
     * Lookup the name in the internal namespace, starting with the current
     * scope. We don't want to add anything new to the namespace here,
     * however, so we use MODE_EXECUTE.
     * Allow searching of the parent tree, but don't open a new scope -
     * we just want to lookup the object (must be mode EXECUTE to perform
     * the upsearch)
     */
    Status = AcpiNsLookup (WalkState->ScopeInfo, Path,
        ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
        ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE, NULL, &Node);

    /*
     * If this name is a control method invocation, we must
     * setup the method call
     */
    if (ACPI_SUCCESS (Status) &&
        PossibleMethodCall &&
        (Node->Type == ACPI_TYPE_METHOD))
    {
        if ((GET_CURRENT_ARG_TYPE (WalkState->ArgTypes) == ARGP_SUPERNAME) ||
            (GET_CURRENT_ARG_TYPE (WalkState->ArgTypes) == ARGP_TARGET))
        {
            /*
             * AcpiPsGetNextNamestring has increased the AML pointer past
             * the method invocation namestring, so we need to restore the
             * saved AML pointer back to the original method invocation
             * namestring.
             */
            WalkState->ParserState.Aml = Start;
            WalkState->ArgCount = 1;
            AcpiPsInitOp (Arg, AML_INT_METHODCALL_OP);
        }

        /* This name is actually a control method invocation */

        MethodDesc = AcpiNsGetAttachedObject (Node);
        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "Control Method invocation %4.4s - %p Desc %p Path=%p\n",
            Node->Name.Ascii, Node, MethodDesc, Path));

        NameOp = AcpiPsAllocOp (AML_INT_NAMEPATH_OP, Start);
        if (!NameOp)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        /* Change Arg into a METHOD CALL and attach name to it */

        AcpiPsInitOp (Arg, AML_INT_METHODCALL_OP);
        NameOp->Common.Value.Name = Path;

        /* Point METHODCALL/NAME to the METHOD Node */

        NameOp->Common.Node = Node;
        AcpiPsAppendArg (Arg, NameOp);

        if (!MethodDesc)
        {
            ACPI_ERROR ((AE_INFO,
                "Control Method %p has no attached object",
                Node));
            return_ACPI_STATUS (AE_AML_INTERNAL);
        }

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "Control Method - %p Args %X\n",
            Node, MethodDesc->Method.ParamCount));

        /* Get the number of arguments to expect */

        WalkState->ArgCount = MethodDesc->Method.ParamCount;
        return_ACPI_STATUS (AE_OK);
    }

    /*
     * Special handling if the name was not found during the lookup -
     * some NotFound cases are allowed
     */
    if (Status == AE_NOT_FOUND)
    {
        /* 1) NotFound is ok during load pass 1/2 (allow forward references) */

        if ((WalkState->ParseFlags & ACPI_PARSE_MODE_MASK) !=
            ACPI_PARSE_EXECUTE)
        {
            Status = AE_OK;
        }

        /* 2) NotFound during a CondRefOf(x) is ok by definition */

        else if (WalkState->Op->Common.AmlOpcode == AML_CONDITIONAL_REF_OF_OP)
        {
            Status = AE_OK;
        }

        /*
         * 3) NotFound while building a Package is ok at this point, we
         * may flag as an error later if slack mode is not enabled.
         * (Some ASL code depends on allowing this behavior)
         */
        else if ((Arg->Common.Parent) &&
            ((Arg->Common.Parent->Common.AmlOpcode == AML_PACKAGE_OP) ||
             (Arg->Common.Parent->Common.AmlOpcode == AML_VARIABLE_PACKAGE_OP)))
        {
            Status = AE_OK;
        }
    }

    /* Final exception check (may have been changed from code above) */

    if (ACPI_FAILURE (Status))
    {
        ACPI_ERROR_NAMESPACE (WalkState->ScopeInfo, Path, Status);

        if ((WalkState->ParseFlags & ACPI_PARSE_MODE_MASK) ==
            ACPI_PARSE_EXECUTE)
        {
            /* Report a control method execution error */

            Status = AcpiDsMethodError (Status, WalkState);
        }
    }

    /* Save the namepath */

    Arg->Common.Value.Name = Path;
    return_ACPI_STATUS (Status);
}