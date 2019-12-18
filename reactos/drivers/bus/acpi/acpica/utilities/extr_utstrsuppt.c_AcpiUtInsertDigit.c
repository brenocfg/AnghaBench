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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAsciiCharToHex (int) ; 
 int /*<<< orphan*/  AcpiUtStrtoulAdd64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtStrtoulMultiply64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtInsertDigit (
    UINT64                  *AccumulatedValue,
    UINT32                  Base,
    int                     AsciiDigit)
{
    ACPI_STATUS             Status;
    UINT64                  Product;


     /* Make room in the accumulated value for the incoming digit */

    Status = AcpiUtStrtoulMultiply64 (*AccumulatedValue, Base, &Product);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Add in the new digit, and store the sum to the accumulated value */

    Status = AcpiUtStrtoulAdd64 (Product, AcpiUtAsciiCharToHex (AsciiDigit),
        AccumulatedValue);

    return (Status);
}