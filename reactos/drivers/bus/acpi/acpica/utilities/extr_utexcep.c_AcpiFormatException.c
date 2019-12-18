#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* Name; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_EXCEPTION_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_1__* AcpiUtValidateException (int /*<<< orphan*/ ) ; 

const char *
AcpiFormatException (
    ACPI_STATUS             Status)
{
    const ACPI_EXCEPTION_INFO   *Exception;


    ACPI_FUNCTION_ENTRY ();


    Exception = AcpiUtValidateException (Status);
    if (!Exception)
    {
        /* Exception code was not recognized */

        ACPI_ERROR ((AE_INFO,
            "Unknown exception code: 0x%8.8X", Status));

        return ("UNKNOWN_STATUS_CODE");
    }

    return (Exception->Name);
}