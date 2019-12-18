#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  AmlOpName; int /*<<< orphan*/  Aml; } ;
struct TYPE_5__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TRACE_AML_OPCODE ; 
 int ACPI_TRACE_OPCODE ; 
 int /*<<< orphan*/  ACPI_TRACE_POINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiExInterpreterTraceEnabled (int /*<<< orphan*/ *) ; 
 int AcpiGbl_TraceFlags ; 
 int /*<<< orphan*/  ExStartTraceOpcode ; 
 int /*<<< orphan*/  TRUE ; 

void
AcpiExStartTraceOpcode (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{

    ACPI_FUNCTION_NAME (ExStartTraceOpcode);


    if (AcpiExInterpreterTraceEnabled (NULL) &&
        (AcpiGbl_TraceFlags & ACPI_TRACE_OPCODE))
    {
        ACPI_TRACE_POINT (ACPI_TRACE_AML_OPCODE, TRUE,
            Op->Common.Aml, Op->Common.AmlOpName);
    }
}