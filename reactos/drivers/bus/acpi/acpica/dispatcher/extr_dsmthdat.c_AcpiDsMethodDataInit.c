#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_9__ {size_t Integer; } ;
struct TYPE_8__ {TYPE_2__* LocalVariables; TYPE_1__* Arguments; } ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; void* Type; void* DescriptorType; TYPE_5__ Name; } ;
struct TYPE_6__ {int /*<<< orphan*/  Flags; void* Type; void* DescriptorType; TYPE_5__ Name; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;

/* Variables and functions */
 void* ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 size_t ACPI_METHOD_NUM_ARGS ; 
 size_t ACPI_METHOD_NUM_LOCALS ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ANOBJ_METHOD_ARG ; 
 int /*<<< orphan*/  ANOBJ_METHOD_LOCAL ; 
 int /*<<< orphan*/  DsMethodDataInit ; 
 int /*<<< orphan*/  NAMEOF_ARG_NTE ; 
 int /*<<< orphan*/  NAMEOF_LOCAL_NTE ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDsMethodDataInit (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;


    ACPI_FUNCTION_TRACE (DsMethodDataInit);


    /* Init the method arguments */

    for (i = 0; i < ACPI_METHOD_NUM_ARGS; i++)
    {
        ACPI_MOVE_32_TO_32 (&WalkState->Arguments[i].Name,
            NAMEOF_ARG_NTE);

        WalkState->Arguments[i].Name.Integer |= (i << 24);
        WalkState->Arguments[i].DescriptorType = ACPI_DESC_TYPE_NAMED;
        WalkState->Arguments[i].Type = ACPI_TYPE_ANY;
        WalkState->Arguments[i].Flags = ANOBJ_METHOD_ARG;
    }

    /* Init the method locals */

    for (i = 0; i < ACPI_METHOD_NUM_LOCALS; i++)
    {
        ACPI_MOVE_32_TO_32 (&WalkState->LocalVariables[i].Name,
            NAMEOF_LOCAL_NTE);

        WalkState->LocalVariables[i].Name.Integer |= (i << 24);
        WalkState->LocalVariables[i].DescriptorType = ACPI_DESC_TYPE_NAMED;
        WalkState->LocalVariables[i].Type = ACPI_TYPE_ANY;
        WalkState->LocalVariables[i].Flags = ANOBJ_METHOD_LOCAL;
    }

    return_VOID;
}