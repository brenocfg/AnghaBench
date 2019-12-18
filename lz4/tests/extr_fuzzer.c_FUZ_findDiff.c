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
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,unsigned int) ; 

__attribute__((used)) static void FUZ_findDiff(const void* buff1, const void* buff2)
{
    const BYTE* const b1 = (const BYTE*)buff1;
    const BYTE* const b2 = (const BYTE*)buff2;
    size_t u = 0;
    while (b1[u]==b2[u]) u++;
    DISPLAY("\nWrong Byte at position %u \n", (unsigned)u);
}