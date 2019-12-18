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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ tolower (int) ; 

void
AcpiUtStrlwr (
    char                    *SrcString)
{
    char                    *String;


    ACPI_FUNCTION_ENTRY ();


    if (!SrcString)
    {
        return;
    }

    /* Walk entire string, lowercasing the letters */

    for (String = SrcString; *String; String++)
    {
        *String = (char) tolower ((int) *String);
    }
}