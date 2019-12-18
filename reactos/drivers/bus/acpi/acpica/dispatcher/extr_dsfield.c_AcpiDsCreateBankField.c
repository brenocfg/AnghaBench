#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
struct TYPE_19__ {int /*<<< orphan*/ * DataRegisterNode; int /*<<< orphan*/ * RegionNode; int /*<<< orphan*/  FieldType; scalar_t__ FieldFlags; int /*<<< orphan*/ * RegisterNode; } ;
struct TYPE_15__ {scalar_t__ Integer; int /*<<< orphan*/  String; int /*<<< orphan*/  Name; TYPE_4__* Arg; } ;
struct TYPE_16__ {TYPE_4__* Next; TYPE_1__ Value; } ;
struct TYPE_18__ {TYPE_2__ Common; } ;
struct TYPE_17__ {int /*<<< orphan*/  ScopeInfo; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_5__ ACPI_CREATE_FIELD_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_NS_SEARCH_PARENT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_BANK_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AcpiDsCreateExternalRegion (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiDsGetFieldNames (TYPE_5__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiNsLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DsCreateBankField ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsCreateBankField (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_NAMESPACE_NODE     *RegionNode,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Arg;
    ACPI_CREATE_FIELD_INFO  Info;


    ACPI_FUNCTION_TRACE_PTR (DsCreateBankField, Op);


    /* First arg is the name of the parent OpRegion (must already exist) */

    Arg = Op->Common.Value.Arg;
    if (!RegionNode)
    {
        Status = AcpiNsLookup (WalkState->ScopeInfo, Arg->Common.Value.Name,
            ACPI_TYPE_REGION, ACPI_IMODE_EXECUTE,
            ACPI_NS_SEARCH_PARENT, WalkState, &RegionNode);
#ifdef ACPI_ASL_COMPILER
        Status = AcpiDsCreateExternalRegion (Status, Arg,
            Arg->Common.Value.Name, WalkState, &RegionNode);
#endif
        if (ACPI_FAILURE (Status))
        {
            ACPI_ERROR_NAMESPACE (WalkState->ScopeInfo,
                Arg->Common.Value.Name, Status);
            return_ACPI_STATUS (Status);
        }
    }

    /* Second arg is the Bank Register (Field) (must already exist) */

    Arg = Arg->Common.Next;
    Status = AcpiNsLookup (WalkState->ScopeInfo, Arg->Common.Value.String,
        ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
        ACPI_NS_SEARCH_PARENT, WalkState, &Info.RegisterNode);
    if (ACPI_FAILURE (Status))
    {
        ACPI_ERROR_NAMESPACE (WalkState->ScopeInfo,
            Arg->Common.Value.String, Status);
        return_ACPI_STATUS (Status);
    }

    /*
     * Third arg is the BankValue
     * This arg is a TermArg, not a constant
     * It will be evaluated later, by AcpiDsEvalBankFieldOperands
     */
    Arg = Arg->Common.Next;

    /* Fourth arg is the field flags */

    Arg = Arg->Common.Next;
    Info.FieldFlags = (UINT8) Arg->Common.Value.Integer;

    /* Each remaining arg is a Named Field */

    Info.FieldType = ACPI_TYPE_LOCAL_BANK_FIELD;
    Info.RegionNode = RegionNode;

    /*
     * Use Info.DataRegisterNode to store BankField Op
     * It's safe because DataRegisterNode will never be used when create
     * bank field \we store AmlStart and AmlLength in the BankField Op for
     * late evaluation. Used in AcpiExPrepFieldValue(Info)
     *
     * TBD: Or, should we add a field in ACPI_CREATE_FIELD_INFO, like
     * "void *ParentOp"?
     */
    Info.DataRegisterNode = (ACPI_NAMESPACE_NODE*) Op;

    Status = AcpiDsGetFieldNames (&Info, WalkState, Arg->Common.Next);
    return_ACPI_STATUS (Status);
}