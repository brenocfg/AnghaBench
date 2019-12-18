#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_INTERPRETER ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExEnterInterpreter ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiExEnterInterpreter (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (ExEnterInterpreter);


    Status = AcpiUtAcquireMutex (ACPI_MTX_INTERPRETER);
    if (ACPI_FAILURE (Status))
    {
        ACPI_ERROR ((AE_INFO, "Could not acquire AML Interpreter mutex"));
    }
    Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    if (ACPI_FAILURE (Status))
    {
        ACPI_ERROR ((AE_INFO, "Could not acquire AML Namespace mutex"));
    }

    return_VOID;
}