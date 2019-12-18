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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  size_t UINT32 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 size_t ACPI_ASCII_ZERO ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t ACPI_MAX32_DECIMAL_DIGITS ; 
 size_t ACPI_MAX64_DECIMAL_DIGITS ; 
 size_t ACPI_MAX8_DECIMAL_DIGITS ; 
 int /*<<< orphan*/  ACPI_MUL_4 (size_t) ; 
 int /*<<< orphan*/  AcpiUtHexToAsciiChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtShortDivide (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static UINT32
AcpiExConvertToAscii (
    UINT64                  Integer,
    UINT16                  Base,
    UINT8                   *String,
    UINT8                   DataWidth)
{
    UINT64                  Digit;
    UINT32                  i;
    UINT32                  j;
    UINT32                  k = 0;
    UINT32                  HexLength;
    UINT32                  DecimalLength;
    UINT32                  Remainder;
    BOOLEAN                 SupressZeros;


    ACPI_FUNCTION_ENTRY ();


    switch (Base)
    {
    case 10:

        /* Setup max length for the decimal number */

        switch (DataWidth)
        {
        case 1:

            DecimalLength = ACPI_MAX8_DECIMAL_DIGITS;
            break;

        case 4:

            DecimalLength = ACPI_MAX32_DECIMAL_DIGITS;
            break;

        case 8:
        default:

            DecimalLength = ACPI_MAX64_DECIMAL_DIGITS;
            break;
        }

        SupressZeros = TRUE;     /* No leading zeros */
        Remainder = 0;

        for (i = DecimalLength; i > 0; i--)
        {
            /* Divide by nth factor of 10 */

            Digit = Integer;
            for (j = 0; j < i; j++)
            {
                (void) AcpiUtShortDivide (Digit, 10, &Digit, &Remainder);
            }

            /* Handle leading zeros */

            if (Remainder != 0)
            {
                SupressZeros = FALSE;
            }

            if (!SupressZeros)
            {
                String[k] = (UINT8) (ACPI_ASCII_ZERO + Remainder);
                k++;
            }
        }
        break;

    case 16:

        /* HexLength: 2 ascii hex chars per data byte */

        HexLength = (DataWidth * 2);
        for (i = 0, j = (HexLength-1); i < HexLength; i++, j--)
        {
            /* Get one hex digit, most significant digits first */

            String[k] = (UINT8)
                AcpiUtHexToAsciiChar (Integer, ACPI_MUL_4 (j));
            k++;
        }
        break;

    default:
        return (0);
    }

    /*
     * Since leading zeros are suppressed, we must check for the case where
     * the integer equals 0
     *
     * Finally, null terminate the string and return the length
     */
    if (!k)
    {
        String [0] = ACPI_ASCII_ZERO;
        k = 1;
    }

    String [k] = 0;
    return ((UINT32) k);
}