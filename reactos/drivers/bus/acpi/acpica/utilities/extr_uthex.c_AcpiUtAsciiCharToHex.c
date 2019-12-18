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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */

UINT8
AcpiUtAsciiCharToHex (
    int                     HexChar)
{

    /* Values 0-9 */

    if (HexChar <= '9')
    {
        return ((UINT8) (HexChar - '0'));
    }

    /* Upper case A-F */

    if (HexChar <= 'F')
    {
        return ((UINT8) (HexChar - 0x37));
    }

    /* Lower case a-f */

    return ((UINT8) (HexChar - 0x57));
}