#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ Type; TYPE_2__* Object; } ;
struct TYPE_15__ {scalar_t__ Value; } ;
struct TYPE_17__ {TYPE_3__ Integer; void* Type; } ;
struct TYPE_16__ {int Count; TYPE_5__* Pointer; } ;
struct TYPE_13__ {scalar_t__ SpaceId; } ;
struct TYPE_14__ {TYPE_1__ Region; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OBJECT_LIST ;
typedef  TYPE_5__ ACPI_OBJECT ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 scalar_t__ ACPI_REG_CONNECT ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiGetHandle (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* AcpiNsGetNextNode (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvOrphanEcRegMethod ; 
 int /*<<< orphan*/  METHOD_NAME__REG ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
AcpiEvOrphanEcRegMethod (
    ACPI_NAMESPACE_NODE     *EcDeviceNode)
{
    ACPI_HANDLE             RegMethod;
    ACPI_NAMESPACE_NODE     *NextNode;
    ACPI_STATUS             Status;
    ACPI_OBJECT_LIST        Args;
    ACPI_OBJECT             Objects[2];


    ACPI_FUNCTION_TRACE (EvOrphanEcRegMethod);


    if (!EcDeviceNode)
    {
        return_VOID;
    }

    /* Namespace is currently locked, must release */

    (void) AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);

    /* Get a handle to a _REG method immediately under the EC device */

    Status = AcpiGetHandle (EcDeviceNode, METHOD_NAME__REG, &RegMethod);
    if (ACPI_FAILURE (Status))
    {
        goto Exit; /* There is no _REG method present */
    }

    /*
     * Execute the _REG method only if there is no Operation Region in
     * this scope with the Embedded Controller space ID. Otherwise, it
     * will already have been executed. Note, this allows for Regions
     * with other space IDs to be present; but the code below will then
     * execute the _REG method with the EmbeddedControl SpaceID argument.
     */
    NextNode = AcpiNsGetNextNode (EcDeviceNode, NULL);
    while (NextNode)
    {
        if ((NextNode->Type == ACPI_TYPE_REGION) &&
            (NextNode->Object) &&
            (NextNode->Object->Region.SpaceId == ACPI_ADR_SPACE_EC))
        {
            goto Exit; /* Do not execute the _REG */
        }

        NextNode = AcpiNsGetNextNode (EcDeviceNode, NextNode);
    }

    /* Evaluate the _REG(EmbeddedControl,Connect) method */

    Args.Count = 2;
    Args.Pointer = Objects;
    Objects[0].Type = ACPI_TYPE_INTEGER;
    Objects[0].Integer.Value = ACPI_ADR_SPACE_EC;
    Objects[1].Type = ACPI_TYPE_INTEGER;
    Objects[1].Integer.Value = ACPI_REG_CONNECT;

    (void) AcpiEvaluateObject (RegMethod, NULL, &Args, NULL);

Exit:
    /* We ignore all errors from above, don't care */

    (void) AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    return_VOID;
}