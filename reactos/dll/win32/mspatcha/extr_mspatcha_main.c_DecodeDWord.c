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
typedef  int UINT ;
typedef  int /*<<< orphan*/  PSAFE_READ ;
typedef  int DWORD ;

/* Variables and functions */
 int ReadByte (int /*<<< orphan*/ ) ; 

DWORD DecodeDWord(PSAFE_READ pRead)
{
    UINT Result = 0, offset;

    for (offset = 0; offset < 32; offset += 7)
    {
        DWORD val = ReadByte(pRead);
        Result |= ((val & 0x7f) << offset);
        if (val & 0x80)
            break;
    }

    return Result;
}