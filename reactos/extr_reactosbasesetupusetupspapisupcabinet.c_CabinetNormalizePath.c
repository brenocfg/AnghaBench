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
typedef  int ULONG ;
typedef  int* PWCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int wcslen (int*) ; 

__attribute__((used)) static BOOL
CabinetNormalizePath(PWCHAR Path,
                     ULONG Length)
{
    ULONG n;
    BOOL Ok;

    n = wcslen(Path);
    Ok = (n + 1) < Length;

    if (n != 0 && Path[n - 1] != L'\\' && Ok)
    {
        Path[n] = L'\\';
        Path[n + 1] = 0;
    }

    return Ok;
}