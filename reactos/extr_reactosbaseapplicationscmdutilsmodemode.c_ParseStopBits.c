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
typedef  int* PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ONE5STOPBITS ; 
 int /*<<< orphan*/  ONESTOPBIT ; 
 int /*<<< orphan*/  TWOSTOPBITS ; 
 scalar_t__ _wcsnicmp (int*,char*,int) ; 

__attribute__((used)) static PCWSTR
ParseStopBits(PCWSTR argStr, PBYTE StopBits)
{
    if (_wcsnicmp(argStr, L"1.5", 3) == 0)
    {
        argStr += 3;
        *StopBits = ONE5STOPBITS;
    }
    else
    {
        if (*argStr == L'1')
            *StopBits = ONESTOPBIT;
        else if (*argStr == L'2')
            *StopBits = TWOSTOPBITS;
        else
            return NULL;

        argStr++;
    }

    return argStr;
}