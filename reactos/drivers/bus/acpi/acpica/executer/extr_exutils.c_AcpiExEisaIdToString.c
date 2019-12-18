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
typedef  scalar_t__ UINT64 ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int AcpiUtDwordByteSwap (int) ; 
 char AcpiUtHexToAsciiChar (scalar_t__,int) ; 

void
AcpiExEisaIdToString (
    char                    *OutString,
    UINT64                  CompressedId)
{
    UINT32                  SwappedId;


    ACPI_FUNCTION_ENTRY ();


    /* The EISAID should be a 32-bit integer */

    if (CompressedId > ACPI_UINT32_MAX)
    {
        ACPI_WARNING ((AE_INFO,
            "Expected EISAID is larger than 32 bits: "
            "0x%8.8X%8.8X, truncating",
            ACPI_FORMAT_UINT64 (CompressedId)));
    }

    /* Swap ID to big-endian to get contiguous bits */

    SwappedId = AcpiUtDwordByteSwap ((UINT32) CompressedId);

    /* First 3 bytes are uppercase letters. Next 4 bytes are hexadecimal */

    OutString[0] = (char) (0x40 + (((unsigned long) SwappedId >> 26) & 0x1F));
    OutString[1] = (char) (0x40 + ((SwappedId >> 21) & 0x1F));
    OutString[2] = (char) (0x40 + ((SwappedId >> 16) & 0x1F));
    OutString[3] = AcpiUtHexToAsciiChar ((UINT64) SwappedId, 12);
    OutString[4] = AcpiUtHexToAsciiChar ((UINT64) SwappedId, 8);
    OutString[5] = AcpiUtHexToAsciiChar ((UINT64) SwappedId, 4);
    OutString[6] = AcpiUtHexToAsciiChar ((UINT64) SwappedId, 0);
    OutString[7] = 0;
}