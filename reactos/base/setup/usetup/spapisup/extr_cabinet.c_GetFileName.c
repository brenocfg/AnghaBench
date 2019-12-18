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

/* Variables and functions */

__attribute__((used)) static PWCHAR
GetFileName(PWCHAR Path)
{
    ULONG i, j;

    j = i = 0;

    while (Path[i++])
    {
        if (Path[i - 1] == L'\\')
            j = i;
    }

    return Path + j;
}