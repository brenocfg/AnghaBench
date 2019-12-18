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
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_3__ {int* Aml; } ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_1__ ACPI_PARSE_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsGetNextPackageLength ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

__attribute__((used)) static UINT32
AcpiPsGetNextPackageLength (
    ACPI_PARSE_STATE        *ParserState)
{
    UINT8                   *Aml = ParserState->Aml;
    UINT32                  PackageLength = 0;
    UINT32                  ByteCount;
    UINT8                   ByteZeroMask = 0x3F; /* Default [0:5] */


    ACPI_FUNCTION_TRACE (PsGetNextPackageLength);


    /*
     * Byte 0 bits [6:7] contain the number of additional bytes
     * used to encode the package length, either 0,1,2, or 3
     */
    ByteCount = (Aml[0] >> 6);
    ParserState->Aml += ((ACPI_SIZE) ByteCount + 1);

    /* Get bytes 3, 2, 1 as needed */

    while (ByteCount)
    {
        /*
         * Final bit positions for the package length bytes:
         *      Byte3->[20:27]
         *      Byte2->[12:19]
         *      Byte1->[04:11]
         *      Byte0->[00:03]
         */
        PackageLength |= (Aml[ByteCount] << ((ByteCount << 3) - 4));

        ByteZeroMask = 0x0F; /* Use bits [0:3] of byte 0 */
        ByteCount--;
    }

    /* Byte 0 is a special case, either bits [0:3] or [0:5] are used */

    PackageLength |= (Aml[0] & ByteZeroMask);
    return_UINT32 (PackageLength);
}