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
struct TYPE_3__ {scalar_t__ Ptr; scalar_t__ Root; scalar_t__ Size; } ;
typedef  TYPE_1__* PSAFE_READ ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */

DWORD ReadDWord(PSAFE_READ pRead)
{
    if (pRead->Ptr + sizeof(DWORD) <= (pRead->Root + pRead->Size))
    {
        DWORD Value = *(PDWORD)pRead->Ptr;
        pRead->Ptr += sizeof(DWORD);
        return Value;
    }
    pRead->Ptr = pRead->Root + pRead->Size;
    return 0;
}