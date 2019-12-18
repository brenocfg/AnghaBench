#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  Parent; } ;
struct TYPE_13__ {int /*<<< orphan*/  AmlStart; int /*<<< orphan*/  AmlLength; } ;
struct TYPE_15__ {TYPE_5__* Node; } ;
struct TYPE_14__ {int Flags; } ;
struct TYPE_16__ {TYPE_1__ Extra; TYPE_3__ BankField; TYPE_2__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_BANK_FIELD ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsExecuteArguments (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* AcpiNsGetSecondaryObject (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtDisplayInitPathname (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (TYPE_5__*) ; 
 int /*<<< orphan*/  DsGetBankFieldArguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsGetBankFieldArguments (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_OPERAND_OBJECT     *ExtraDesc;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (DsGetBankFieldArguments, ObjDesc);


    if (ObjDesc->Common.Flags & AOPOBJ_DATA_VALID)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Get the AML pointer (method object) and BankField node */

    ExtraDesc = AcpiNsGetSecondaryObject (ObjDesc);
    Node = ObjDesc->BankField.Node;

    ACPI_DEBUG_EXEC (AcpiUtDisplayInitPathname (
        ACPI_TYPE_LOCAL_BANK_FIELD, Node, NULL));

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "[%4.4s] BankField Arg Init\n",
        AcpiUtGetNodeName (Node)));

    /* Execute the AML code for the TermArg arguments */

    Status = AcpiDsExecuteArguments (Node, Node->Parent,
        ExtraDesc->Extra.AmlLength, ExtraDesc->Extra.AmlStart);
    return_ACPI_STATUS (Status);
}