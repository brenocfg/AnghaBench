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
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtDeleteAddressLists () ; 
 int /*<<< orphan*/  AcpiUtFreeGpeLists () ; 
 int /*<<< orphan*/  UtTerminate ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
AcpiUtTerminate (
    void)
{
    ACPI_FUNCTION_TRACE (UtTerminate);

    AcpiUtFreeGpeLists ();
    AcpiUtDeleteAddressLists ();
    return_VOID;
}